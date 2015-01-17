var gulp = require('gulp')
  ,shell = require('gulp-shell');

gulp.task('default', function() {

});

// Need to nuke d7 directory before Drush making
gulp.task
// Drush make drupal and contrib modules
gulp.task('drupal7:make', shell.task('drush make build/d7-generate.make web/drupal/d7'));
// Copy local settings.php to new local d7 site
gulp.task('drupal7:localCreds', function() {
  gulp
    .src([
      'build/config/d7/d7.local.downfallguild.org/**/*'
    ]).pipe(
      gulp.dest('web/drupal/d7/sites/d7.local.downfallguild.org')
    );
});
