var gulp = require('gulp')
  ,shell = require('gulp-shell')
  ,del = require('del')
  ,watch = require('gulp-watch')
  ,chmod = require('gulp-chmod');

gulp.task('default', function() {

});

// Need to nuke d7 directory before Drush making
//gulp.task('d7:chmod', function() {
//  return gulp.src('web/drupal/d7/**/*')
//    .pipe(chmod(777));
//});

gulp.task('d7:clean', function(cb) {
  del(['web/drupal/d7'], cb);
});

// Drush make drupal and contrib modules
gulp.task('d7:make', ['d7:clean'], function() {
  return gulp.src('')
    .pipe(
      shell(['drush make build/d7-generate.make web/drupal/d7'])
    );
});

// Copy local settings.php to new local d7 site
gulp.task('d7:customFiles', ['d7:make'], function() {
  return gulp.src([
      'build/dev/d7/**/*'
    ]).pipe(
      gulp.dest('web/drupal/d7/sites/')
    );
});

// Full drupal install
gulp.task('d7:install', ['d7:customFiles'], function() {
  return gulp.src('')
    .pipe(
      shell([
        'echo "Installing drupal, make sure you catch the password printed out"',
        'drush site-install standard --site-name=DOWNFALLD7 --yes',
        'echo "Enabling downfall_migrate_feature"',
        'drush en downfall_migrate_feature --yes',
        'echo "Rebuilding node access permissons"',
        'drush php-eval "node_access_rebuild();"'
      ], {
        'cwd':'web/drupal/d7/sites/d7.local.downfallguild.org'
      })
    );
});

// Kick off d7 build
gulp.task('d7:init', ['d7:install']);

gulp.task('d7:cc', function() {
  return gulp.src('')
    .pipe(
      shell(['drush cc all'], {'cwd': 'web/drupal/d7/sites/d7.local.downfallguild.org'})
    );
});

gulp.task('d7:watch', function() {
  return gulp.src('build/dev/d7/**/*')
    .pipe(watch('build/dev/d7/**/*'))
    //.pipe(gulp.dest('web/drupal/d7/sites/'));
    .pipe(shell(['rsync -vzr /var/www/build/dev/d7/* /var/www/web/drupal/d7/sites']));
});


// D6 Work
gulp.task('d6:init', function() {
  return gulp.src('')
    .pipe(shell([
        'rsync -zvrP illepic@direct.downfallguild.org:webapps/downfall_drupal/* /var/www/web/drupal/d6',
        'rsync -zvrP /var/www/build/dev/d6/* /var/www/web/drupal/d6/sites'
      ])
    );
});