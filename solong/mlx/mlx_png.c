

#include <stdlib.h>
#include <stdio.h>
#include <sys/mman.h>
#include <unistd.h>
#include <fcntl.h>
#include <err.h>
#include <string.h>
#include <arpa/inet.h>

#include "zlib.h"

#include <OpenGL/gl3.h>
#include	"mlx_int.h"


#define	PNG_MAGIC_SIZE	8
unsigned char magic[PNG_MAGIC_SIZE] = {137, 80, 78, 71, 13, 10, 26, 10};
#define PNG_HDR_SIZE	13

#define	Z_CHUNK	32768

#define	ERR_MAGIC_SIZE	1
#define	ERR_MAGIC_WRONG	2
#define	ERR_STRUCT_INCOMPLETE	3
#define	ERR_STRUCT_HDR	4
#define	ERR_STRUCT_END	5
#define	ERR_STRUCT_CRC	6
#define	ERR_STRUCT_INCIMPL 7
#define	ERR_STRUCT_DAT	8
#define	ERR_STRUCT_MISSCHK	9
#define	ERR_ZLIB	10
#define	ERR_DATA_MISMATCH	11
#define	ERR_DATA_FILTER	12
char *(mipng_err[]) =
{
  "No error",
  "Not enough size for magic",
  "Wrong magic",
  "Incomplete chunk structure",
  "Duplicate or incorrect header",
  "Duplicate or incorrect end",
  "Invalid CRC in chunk",
  "Incorrect header or configuration not implemented",
  "Non consecutive dat chunks",
  "Missing header/dat/end chunk(s)",
  "Zlib inflate error",
  "Inflated data size mismatch",
  "Unknown scanline filter"
};

typedef struct png_info_s
{
  unsigned int	width;
  unsigned int	height;
  int		depth;
  int		color;
  int		interlace;
  int		bpp;
} png_info_t;


int	mipng_is_type(unsigned char *ptr, char *type)
{
  if (ptr[4] == type[0] && ptr[5] == type[1] && ptr[6] == type[2] && ptr[7] == type[3])
    return (1);
  return (0);
}


unsigned char mipng_defilter_none(unsigned char *buff, int pos, int a, int b, int c)
{ return (buff[pos]); }
unsigned char mipng_defilter_sub(unsigned char *buff, int pos, int a, int b, int c)
{ return (buff[pos]+(unsigned int)a); }
unsigned char mipng_defilter_up(unsigned char *buff, int pos, int a, int b, int c)
{ return (buff[pos]+(unsigned int)b); }
unsigned char mipng_defilter_average(unsigned char *buff, int pos, int a, int b, int c)
{ return (buff[pos]+((unsigned int)a+(unsigned int)b)/2); }
unsigned char mipng_defilter_paeth(unsigned char *buff, int pos, int a, int b, int c)
{
  int	p;
  int	result;

  p = a + b - c;
  if (abs(b - c) <= abs(a - c) && abs(b - c) <= abs(a + b - c - c))
    result = a;
  else
    if (abs(a - c) <= abs(a + b - c - c))
      result = b;
    else
      result = c;
 return (buff[pos]+result);
}



unsigned char (*(mipng_defilter[]))(unsigned char *buff, int pos, int a, int b, int c) =
{
  mipng_defilter_none,
  mipng_defilter_sub,
  mipng_defilter_up,
  mipng_defilter_average,
  mipng_defilter_paeth
};

// only work for mlx mac or img 32bpp
int	mipng_fill_img(mlx_img_list_t *img, unsigned char *buf, png_info_t *pi)
{
  unsigned int	current_filter;
  int	ipos;
  int	bpos;
  int	ilen;
  int	iline;
  int	blen;
  unsigned char tmp;
  unsigned char *ibuf;

  ibuf = (unsigned char *)img->buffer;
  iline = img->width * UNIQ_BPP;
  ilen = img->width * img->height * UNIQ_BPP;
  blen = img->width * img->height * pi->bpp + img->height;
  ipos = 0;
  bpos = 0;
  while (ipos < ilen && bpos < blen)
    {
      if ((ipos % iline) == 0)
	{
	  if ((current_filter = buf[bpos++]) > 4)
	    return (ERR_DATA_FILTER);
	}
      ibuf[ipos] = mipng_defilter[current_filter](buf, bpos,
				 ipos%iline>3?ibuf[ipos-UNIQ_BPP]:0,
				 (ipos>=iline)?ibuf[ipos-iline]:0,
				 (ipos>=iline && ipos%iline>3)?ibuf[ipos-iline-UNIQ_BPP]:0);
      ipos ++;
      bpos ++;
      if (pi->depth == 16)
	bpos ++;
      if (ipos % 4 == 3 && pi->color == 2)  // no alpha
	img->buffer[ipos++] = 0xFF;
    }
  if (ipos != ilen || bpos != blen)
    {
      //      printf("fill err ipos %d vs %d, bpos %d vs %d\n", ipos, ilen, bpos, blen);
      return (ERR_DATA_MISMATCH);
    }
  ipos = 0;
  while (ipos < ilen)
    {
      tmp = ibuf[ipos];
      ibuf[ipos] = ibuf[ipos+2];
      ibuf[ipos+2] = tmp;
      ibuf[ipos+3] = 0xFF - ibuf[ipos+3];
      ipos += UNIQ_BPP;
    }
  return (0);
}


int	mipng_data(mlx_img_list_t *img, unsigned char *dat, png_info_t *pi)
{
  unsigned int	len;
  int		b_pos;
  unsigned char *buffer;
  int		ret;
  int z_ret;
  unsigned z_have;
  z_stream z_strm;
  unsigned char z_out[Z_CHUNK];

  b_pos = 0;
  if (!(buffer = malloc((long long)img->width*(long long)img->height*(long long)pi->bpp + img->height)))
    err(1, "Can't malloc");
  z_strm.zalloc = Z_NULL;
  z_strm.zfree = Z_NULL;
  z_strm.opaque = Z_NULL;
  z_strm.avail_in = 0;
  z_strm.next_in = Z_NULL;
  z_ret = inflateInit(&z_strm);
  if (z_ret != Z_OK)
    return (ERR_ZLIB);

  while (mipng_is_type(dat, "IDAT"))
    {
      len = *((unsigned int *)dat);
      len = ntohl(len);
      z_strm.avail_in = len;
      z_strm.next_in = dat + 8;
      z_strm.avail_out = 0;
      while (z_strm.avail_out == 0)
	{
	  z_strm.avail_out = Z_CHUNK;
	  z_strm.next_out = z_out;
	  z_ret = inflate(&z_strm, Z_NO_FLUSH);
	  //	  printf("inflate ret %d avail_out %d\n", z_ret, z_strm.avail_out);
	  if (z_ret != Z_OK && z_ret != Z_STREAM_END)
	    {
	      inflateEnd(&z_strm);
	      return (ERR_ZLIB);
	    }
	  if (b_pos + Z_CHUNK - z_strm.avail_out > img->width*img->height*pi->bpp+img->height)
	    {
	      inflateEnd(&z_strm);
	      return (ERR_DATA_MISMATCH);
	    }
	  bcopy(z_out, buffer+b_pos, Z_CHUNK - z_strm.avail_out);
	  b_pos += Z_CHUNK - z_strm.avail_out;
	}
      dat += len + 4 + 4 + 4;
    } 
  inflateEnd(&z_strm);
  if (b_pos != img->width*img->height*pi->bpp+img->height)
    {
      //      printf("pb : bpos %d vs expected %d\n", b_pos, img->width*img->height*pi->bpp+img->height);
      return (ERR_DATA_MISMATCH);
    }
  if ((ret = mipng_fill_img(img, buffer, pi)))
    return (ret);
  return (0);
}



int	mipng_magic(unsigned char *ptr, int size)
{
  int	i;

  if (size < PNG_MAGIC_SIZE)
    return (ERR_MAGIC_SIZE);
  i = 0;
  while (i < PNG_MAGIC_SIZE)
    if (*(ptr++) != magic[i++])
      return (ERR_MAGIC_WRONG);
  return (0);
}


unsigned long crc_table[256] = { 0, 0x77073096, 0xee0e612c, 0x990951ba, 0x76dc419, 0x706af48f, 0xe963a535, 0x9e6495a3, 0xedb8832, 0x79dcb8a4, 0xe0d5e91e, 0x97d2d988, 0x9b64c2b, 0x7eb17cbd, 0xe7b82d07, 0x90bf1d91, 0x1db71064, 0x6ab020f2, 0xf3b97148, 0x84be41de, 0x1adad47d, 0x6ddde4eb, 0xf4d4b551, 0x83d385c7, 0x136c9856, 0x646ba8c0, 0xfd62f97a, 0x8a65c9ec, 0x14015c4f, 0x63066cd9, 0xfa0f3d63, 0x8d080df5, 0x3b6e20c8, 0x4c69105e, 0xd56041e4, 0xa2677172, 0x3c03e4d1, 0x4b04d447, 0xd20d85fd, 0xa50ab56b, 0x35b5a8fa, 0x42b2986c, 0xdbbbc9d6, 0xacbcf940, 0x32d86ce3, 0x45df5c75, 0xdcd60dcf, 0xabd13d59, 0x26d930ac, 0x51de003a, 0xc8d75180, 0xbfd06116, 0x21b4f4b5, 0x56b3c423, 0xcfba9599, 0xb8bda50f, 0x2802b89e, 0x5f058808, 0xc60cd9b2, 0xb10be924, 0x2f6f7c87, 0x58684c11, 0xc1611dab, 0xb6662d3d, 0x76dc4190, 0x1db7106, 0x98d220bc, 0xefd5102a, 0x71b18589, 0x6b6b51f, 0x9fbfe4a5, 0xe8b8d433, 0x7807c9a2, 0xf00f934, 0x9609a88e, 0xe10e9818, 0x7f6a0dbb, 0x86d3d2d, 0x91646c97, 0xe6635c01, 0x6b6b51f4, 0x1c6c6162, 0x856530d8, 0xf262004e, 0x6c0695ed, 0x1b01a57b, 0x8208f4c1, 0xf50fc457, 0x65b0d9c6, 0x12b7e950, 0x8bbeb8ea, 0xfcb9887c, 0x62dd1ddf, 0x15da2d49, 0x8cd37cf3, 0xfbd44c65, 0x4db26158, 0x3ab551ce, 0xa3bc0074, 0xd4bb30e2, 0x4adfa541, 0x3dd895d7, 0xa4d1c46d, 0xd3d6f4fb, 0x4369e96a, 0x346ed9fc, 0xad678846, 0xda60b8d0, 0x44042d73, 0x33031de5, 0xaa0a4c5f, 0xdd0d7cc9, 0x5005713c, 0x270241aa, 0xbe0b1010, 0xc90c2086, 0x5768b525, 0x206f85b3, 0xb966d409, 0xce61e49f, 0x5edef90e, 0x29d9c998, 0xb0d09822, 0xc7d7a8b4, 0x59b33d17, 0x2eb40d81, 0xb7bd5c3b, 0xc0ba6cad, 0xedb88320, 0x9abfb3b6, 0x3b6e20c, 0x74b1d29a, 0xead54739, 0x9dd277af, 0x4db2615, 0x73dc1683, 0xe3630b12, 0x94643b84, 0xd6d6a3e, 0x7a6a5aa8, 0xe40ecf0b, 0x9309ff9d, 0xa00ae27, 0x7d079eb1, 0xf00f9344, 0x8708a3d2, 0x1e01f268, 0x6906c2fe, 0xf762575d, 0x806567cb, 0x196c3671, 0x6e6b06e7, 0xfed41b76, 0x89d32be0, 0x10da7a5a, 0x67dd4acc, 0xf9b9df6f, 0x8ebeeff9, 0x17b7be43, 0x60b08ed5, 0xd6d6a3e8, 0xa1d1937e, 0x38d8c2c4, 0x4fdff252, 0xd1bb67f1, 0xa6bc5767, 0x3fb506dd, 0x48b2364b, 0xd80d2bda, 0xaf0a1b4c, 0x36034af6, 0x41047a60, 0xdf60efc3, 0xa867df55, 0x316e8eef, 0x4669be79, 0xcb61b38c, 0xbc66831a, 0x256fd2a0, 0x5268e236, 0xcc0c7795, 0xbb0b4703, 0x220216b9, 0x5505262f, 0xc5ba3bbe, 0xb2bd0b28, 0x2bb45a92, 0x5cb36a04, 0xc2d7ffa7, 0xb5d0cf31, 0x2cd99e8b, 0x5bdeae1d, 0x9b64c2b0, 0xec63f226, 0x756aa39c, 0x26d930a, 0x9c0906a9, 0xeb0e363f, 0x72076785, 0x5005713, 0x95bf4a82, 0xe2b87a14, 0x7bb12bae, 0xcb61b38, 0x92d28e9b, 0xe5d5be0d, 0x7cdcefb7, 0xbdbdf21, 0x86d3d2d4, 0xf1d4e242, 0x68ddb3f8, 0x1fda836e, 0x81be16cd, 0xf6b9265b, 0x6fb077e1, 0x18b74777, 0x88085ae6, 0xff0f6a70, 0x66063bca, 0x11010b5c, 0x8f659eff, 0xf862ae69, 0x616bffd3, 0x166ccf45, 0xa00ae278, 0xd70dd2ee, 0x4e048354, 0x3903b3c2, 0xa7672661, 0xd06016f7, 0x4969474d, 0x3e6e77db, 0xaed16a4a, 0xd9d65adc, 0x40df0b66, 0x37d83bf0, 0xa9bcae53, 0xdebb9ec5, 0x47b2cf7f, 0x30b5ffe9, 0xbdbdf21c, 0xcabac28a, 0x53b39330, 0x24b4a3a6, 0xbad03605, 0xcdd70693, 0x54de5729, 0x23d967bf, 0xb3667a2e, 0xc4614ab8, 0x5d681b02, 0x2a6f2b94, 0xb40bbe37, 0xc30c8ea1, 0x5a05df1b, 0x2d02ef8d };

// From http://www.w3.org/TR/PNG/#D-CRCAppendix
int	mipng_crc(unsigned char *ptr, int len)
{
  unsigned int	file_crc;
  unsigned long crc;
  int		i;

  file_crc = *((unsigned int *)(ptr+4+4+len));
  file_crc = ntohl(file_crc);
  
  crc = 0xffffffffL;
  i = 0;
  while (i < len+4)
    crc = crc_table[(crc ^ ptr[(i++)+4]) & 0xff] ^ (crc >> 8);
  crc ^= 0xffffffffL;

  if (file_crc != crc)
    return (1);
  return (0);
}


int	mipng_structure(unsigned char *ptr, int size, unsigned char **hdr, unsigned char **dat)
{
  unsigned int	len;
  int		dat_state;
  int		end;

  dat_state = 0;
  *hdr = NULL;
  *dat = NULL;
  end = 0;
  while (size)
    {
      if (size >= 4) // length present
	{
	  len = *((unsigned int *)ptr);
	  len = ntohl(len);
	  if (size < 4 + 4 + 4 + len)
	    return (ERR_STRUCT_INCOMPLETE);
	  if (mipng_crc(ptr, len))
	    return (ERR_STRUCT_CRC);
	  //	  printf("found chunk len %d type %c%c%c%c\n", len, *(ptr+4), *(ptr+5), *(ptr+6), *(ptr+7));
	  if (mipng_is_type(ptr, "IHDR"))
	    {
	      if (*hdr || len != PNG_HDR_SIZE)
		return (ERR_STRUCT_HDR);
	      *hdr = ptr;
	    }
	  if (mipng_is_type(ptr, "IEND"))
	    {
	      if (len != 0 || size != 4+4+4)
		return (ERR_STRUCT_END);
	      end = 1;
	    }
	  if (mipng_is_type(ptr, "IDAT"))
	    {
	      if (dat_state == 0)
		{
		  dat_state = 1;
		  *dat = ptr;
		}
	      if (dat_state == 2)
		return (ERR_STRUCT_DAT);
	    }
	  else
	    if (dat_state == 1)
	      dat_state = 2;
	  size -= 4+4+4+len;
	  ptr += 4+4+4+len;
	}
      else
	return (ERR_STRUCT_INCOMPLETE);
    }
  if (*hdr == 0 || *dat == 0 || end == 0)
    return (ERR_STRUCT_MISSCHK);
  return (0);
}


int	mipng_verif_hdr(unsigned char *hdr, png_info_t *pi)
{
  unsigned int	compress;
  unsigned int	filter;

  hdr += 8;
  pi->width = ntohl(*((unsigned long *)hdr));
  pi->height = ntohl(*((unsigned long *)(hdr+4)));
  pi->depth = *(hdr+8);
  pi->color = *(hdr+9);
  compress = *(hdr+10);
  filter = *(hdr+11);
  pi->interlace = *(hdr+12);
  if (pi->width <= 0 || pi->height <= 0 || (pi->depth != 8 && pi->depth != 16)
      || (pi->color != 2 && pi->color != 6) || compress != 0 || filter != 0 || pi->interlace != 0)
    return (ERR_STRUCT_INCIMPL);
  pi->bpp = pi->depth / 8;
  if (pi->color == 2)
    pi->bpp *= 3;
  if (pi->color == 6)
    pi->bpp *= 4;
  //  printf("hdr info : %d x %d, depth %d, col type %d, comp %d, filter %d, interlace %d\nbpp is %d\n",
  //	 pi->width, pi->height, pi->depth, pi->color, compress, filter, pi->interlace, pi->bpp);
  return (0);
}


mlx_img_list_t	*mlx_int_parse_png(mlx_ptr_t *xvar, unsigned char *fptr, int size)
{
  int		err;
  unsigned char *hdr;
  unsigned char *dat;
  png_info_t	pi;
  mlx_img_list_t *img;

  if ((err = mipng_magic(fptr, size)))
    {
      warnx("mlx PNG error : %s", mipng_err[err]);
      return ((mlx_img_list_t *)0);
    }
  fptr += PNG_MAGIC_SIZE;
  size -= PNG_MAGIC_SIZE;
  if ((err = mipng_structure(fptr, size, &hdr, &dat)))
    {
      warnx("mlx PNG error : %s", mipng_err[err]);
      return ((mlx_img_list_t *)0);
    }
  if ((err = mipng_verif_hdr(hdr, &pi)))
    {
      warnx("mlx PNG error : %s", mipng_err[err]);
      return ((mlx_img_list_t *)0);
    }
  if (!(img = mlx_new_image(xvar, pi.width, pi.height)))
    {
      warnx("mlx PNG error : Can't create mlx image");
      return ((mlx_img_list_t *)0);
    }
  if ((err = mipng_data(img, dat, &pi)))
    {
      mlx_destroy_image(xvar, img);
      warnx("mlx PNG error : %s", mipng_err[err]);
      return ((mlx_img_list_t *)0);
    }
  return (img);
}




void	*mlx_png_file_to_image(mlx_ptr_t *xvar, char *file, int *width, int *height)
{
  int			fd;
  int			size;
  unsigned char		*ptr;
  mlx_img_list_t        *img;

  if ((fd = open(file, O_RDONLY)) == -1 || (size = lseek(fd, 0, SEEK_END)) == -1 ||
      (ptr = mmap(0, size, PROT_READ, MAP_PRIVATE, fd, 0)) == (void *)MAP_FAILED)
    {
      if (fd >= 0)
        close(fd);
      warnx("Can't map png file '%s'", file);
      return ((void *)0);
    }
  if ((img = mlx_int_parse_png(xvar, ptr, size)))
    {
      *width = img->width;
      *height = img->height;
    }
  else
    {
      *width = 0;
      *height = 0;
    }
  munmap(ptr,size);
  close(fd);
  return (img);
}
