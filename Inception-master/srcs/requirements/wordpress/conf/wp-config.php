<?php
################################################################### INFO ####################################################################

### for wordpress helpful sites ###
# https://developer.wordpress.org/apis/wp-config-php/#default-wp-config-sample-php
# https://core.trac.wordpress.org/browser/trunk/wp-config-sample.php
# https://core.trac.wordpress.org/export/56319/trunk/wp-config-sample.php

### how to find wp-config-sample.php file ###
# $> docker pull wordpress
# $> docker run -it wordpress
# find /var/www/html/wp-config-sample.php
# find /var/www/html/wp-config.php

### wp-config.php'nin önemi ###
# wp-config.php, WordPress'in en önemli dosyalarından biridir.
# WordPress'in veritabanını, şifreleme ayarlarını ve diğer önemli ayarları içerir.
# wp-config.php dosyası, WordPress'i kurmadan önce oluşturulmalıdır.
# Dosyayı oluşturmak için, WordPress kurulum dosyasının içinde bulunan wp-config.php.sample dosyasını kopyalayabilir ve wp-config.php olarak yeniden adlandırabilirsiniz.
# Ardından, wp-config.php dosyasını metin düzenleyicisi ile açarak, veritabanı bağlantı bilgilerinizi, şifreleme ayarlarınızı ve diğer önemli ayarlarınızı ekleyebilirsiniz.
# wp-config.php dosyası, WordPress'in düzgün çalışması için gereklidir.
# Dosyada yapılan herhangi bir değişiklik, WordPress'in düzgün çalışmamasına neden olabilir.

#############################################################################################################################################
?>

<?php
define( 'WP_SITEURL', 'https://uercan.42.fr' );
define( 'WP_HOME', 'https://uercan.42.fr' );
/**
 * The base configuration for WordPress
 *
 * The wp-config.php creation script uses this file during the installation.
 * You don't have to use the web site, you can copy this file to "wp-config.php"
 * and fill in the values.
 *
 * This file contains the following configurations:
 *
 * * Database settings
 * * Secret keys
 * * Database table prefix
 * * ABSPATH
 *
 * @link https://wordpress.org/documentation/article/editing-wp-config-php/
 *
 * @package WordPress
 */

// ** Database settings - You can get this info from your web host ** //
/** The name of the database for WordPress */
define( 'DB_NAME', 'wordpress' );

/** Database username */
define( 'DB_USER', 'uercan' );

/** Database password */
define( 'DB_PASSWORD', '1234' );

/** Database hostname */
define( 'DB_HOST', 'mariadb' );

/** Database charset to use in creating database tables. */
define( 'DB_CHARSET', 'utf8' );

/** The database collate type. Don't change this if in doubt. */
define( 'DB_COLLATE', '' );

/**#@+
 * Authentication unique keys and salts.
 *
 * Change these to different unique phrases! You can generate these using
 * the {@link https://api.wordpress.org/secret-key/1.1/salt/ WordPress.org secret-key service}.
 *
 * You can change these at any point in time to invalidate all existing cookies.
 * This will force all users to have to log in again.
 *
 * @since 2.6.0
 */
define( 'AUTH_KEY',         'put your unique phrase here' );
define( 'SECURE_AUTH_KEY',  'put your unique phrase here' );
define( 'LOGGED_IN_KEY',    'put your unique phrase here' );
define( 'NONCE_KEY',        'put your unique phrase here' );
define( 'AUTH_SALT',        'put your unique phrase here' );
define( 'SECURE_AUTH_SALT', 'put your unique phrase here' );
define( 'LOGGED_IN_SALT',   'put your unique phrase here' );
define( 'NONCE_SALT',       'put your unique phrase here' );

/**#@-*/

/**
 * WordPress database table prefix.
 *
 * You can have multiple installations in one database if you give each
 * a unique prefix. Only numbers, letters, and underscores please!
 */
$table_prefix = 'wp_';

/**
 * For developers: WordPress debugging mode.
 *
 * Change this to true to enable the display of notices during development.
 * It is strongly recommended that plugin and theme developers use WP_DEBUG
 * in their development environments.
 *
 * For information on other constants that can be used for debugging,
 * visit the documentation.
 *
 * @link https://wordpress.org/documentation/article/debugging-in-wordpress/
 */
define( 'WP_DEBUG', false );

/* Add any custom values between this line and the "stop editing" line. */



/* That's all, stop editing! Happy publishing. */

/** Absolute path to the WordPress directory. */
if ( ! defined( 'ABSPATH' ) ) {
        define( 'ABSPATH', __DIR__ . '/' );
}

/** Sets up WordPress vars and included files. */
require_once ABSPATH . 'wp-settings.php';