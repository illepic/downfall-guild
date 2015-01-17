var gulp = require('gulp')
  ,shell = require('gulp-shell')
  ,del = require('del');

gulp.task('default', function() {

});

// Need to nuke d7 directory before Drush making
gulp.task('d7:clean', function(cb) {
  del([
    'web/drupal/d7'
  ], cb);
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
      'build/config/d7/**/*'
    ]).pipe(
      gulp.dest('web/drupal/d7/sites/')
    );
});

// Kick off d7 build
gulp.task('d7:init', ['d7:customFiles']);

gulp.task('d7:cc', function() {
  return gulp.src('')
    .pipe(
      shell(['drush cc all'], {'cwd': '/var/www/web/drupal/d7/sites/d7.local.downfallguild.org'})
    );
});