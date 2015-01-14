core = 6.x
api = 2

libraries[phpmailer][download][type] = "get"
libraries[phpmailer][download][url] = "http://downloads.sourceforge.net/project/phpmailer/phpmailer%20for%20php5_6/Previous%20Versions/2.2.1/phpMailer_v2.2.1_.tar.gz"
libraries[phpmailer][download][md5] = "0bf75c1bcef8bde6adbebcdc69f1a02d"
libraries[phpmailer][directory_name] = "phpmailer"
libraries[phpmailer][destination] = "modules/contrib/smtp"

libraries[phpmailer][patch][drupal-compatibility][url] = "http://drupalcode.org/project/smtp.git/blob_plain/2acaba97adcad7304c22624ceeb009d358b596e3:/class.phpmailer.php.2.2.1.patch"
libraries[phpmailer][patch][drupal-compatibility][md5] = "2d82de03b1a4b60f3b69cc20fae61b76"
