var gulp = require('gulp')
  ,symlink = require('gulp-symlink')
  ,runSequence = require('run-sequence')
  ,git = require('gulp-git')
  ,browserSync = require('browser-sync')
  ,reload = browserSync.reload
  ,sass = require('gulp-sass')
  ,exec = require('gulp-exec');

gulp.task('default', function() {

});

// Check for and cloen the Drupal VM repo
gulp.task('drupalVM:repo', function() {

  var config = ['config/config.yml', 'config/drupal.make.yml'];
  var dest = 'drupal-vm';

  git.clone('git@github.com:geerlingguy/drupal-vm.git', function (err) {
    if (err == null) {

      console.log('Clone successful, copying config');

      return gulp.src(config)
        .pipe(gulp.dest(dest));

    } else {

      console.log('Folder exists, updating repo, copying config');

      git.pull('origin', 'master', {cwd: 'drupal-vm'}, function(err) {

        //if (err) throw err;

        return gulp.src(config)
          .pipe(gulp.dest(dest));

      });
    }
  });

});

// Symlink into the Drupal VM repo our custom config files
gulp.task('drupalVM:copy:VMConfig', function() {
  console.log('Writing config to vm');
  return gulp.src(['config/config.yml', 'config/drupal.make.yml'])
    .pipe(gulp.dest('drupal-vm'));
});

// Restart vagrant: this changes the server AND rebuilds drupal if we've deleted it
var vagrantoptions = {
  cwd: __dirname + '/drupal-vm',
  continueOnError: false,
  pipeStdout: false
};
gulp.task('drupalVM:vagrantUp', function() {
  return gulp.src('')
    .pipe(exec('vagrant halt && vagrant up --provision', vagrantoptions)
    );
});

// Symlink our local custom drupal module dev work
gulp.task('d8:symlink:D8Modules', function() {
  return gulp.src('project/build/dev/d8/modules/custom')
    .pipe(symlink('project/web/d8/modules/custom', {force: true}));
});

// Run each task consecutively
gulp.task('d8:rebuild', function(callback) {
  runSequence(
    'drupalVM:repo',
    'drupalVM:copy:VMConfig',
    'drupalVM:vagrantUp',
    'd8:symlink:D8Modules',
    callback
  );
});

// PL stuff
//gulp.task('pl:gulp:package', function() {
//  return gulp.src('./node_modules/patternlab-node/package.gulp.json')
//    .pipe(gulp.dest('./node_modules/patternlab-node/package.json'));
//});
//gulp.task('pl:npm:install', ['pl:gulp:package'], function() {
//  return gulp.src('')
//    .pipe(shell(['npm install'], {cwd: 'node_modules/patternlab-node'}));
//});
//gulp.task('pl:symlink', ['pl:npm:install'], function() {
//  return gulp.src('redesign/pl/source')
//    .pipe(shell(['rm -rf node_modules/patternlab-node/source']))
//    .pipe(symlink('node_modules/patternlab-node/source', {force: true}));
//});

var ploptions = {
  cwd: __dirname + '/redesign/pl',
  continueOnError: false,
  pipeStdout: false
};

// First, full build of PL. Only needs to run once
gulp.task('pl:build', function() {
  return gulp.src('')
    .pipe(
      exec('gulp lab', ploptions)
    );
});

//var exec = require('child_process').exec;

// Rebuild patterns
gulp.task('pl:patternlab', function() {
  return gulp.src('')
    .pipe(exec('gulp lab', ploptions));
});
gulp.task('watch-pl:patternlab', ['pl:patternlab'], reload);

// Sass
gulp.task('browser-sync', function() {
  browserSync({
      startPath: 'redesign/pl/public',
      server: {
        baseDir: './'
      }
  });
});
gulp.task('sass', function() {
  return gulp.src('redesign/assets/src/sass/style.scss')
    .pipe(sass({
      sourceMap: true,
      outputStyle: 'expanded',
      includePaths: ['redesign/assets/src/sass']
    }))
    .pipe(gulp.dest('redesign/assets/compiled/css'))
    .pipe(reload({stream: true}));
});

gulp.task('proto:reload', reload);

// Prototype watch
gulp.task('proto', ['sass', 'pl:build', 'browser-sync'], function() {
  gulp.watch('redesign/assets/src/sass/**/*.scss', ['sass']);

  gulp.watch([
    'redesign/pl/source/_patterns/**/*.mustache',
    'redesign/pl/source/_patterns/**/*.json',
    'redesign/pl/source/_data/*.json'], ['watch-pl:patternlab']);

  gulp.watch('redesign/assets/src/js/**/*.js', ['proto:reload']);

});

// D6 Work
//gulp.task('d6:sync', function() {
//  return gulp.src('')
//    .pipe(shell(['rsync -zvrP ' + argv.user + '@direct.illepic.com:webapps/downfall_drupal/ d6/'], {cwd: 'project/web'}));
//});

// ====================== OLD BELOW ================================

// Blow away D8
//gulp.task('d8:ownD8', function() {
//  return gulp.src(['project/web/d8', 'project/web/d8/**/*'])
//  .pipe(chmod(755))
//});
//gulp.task('d8:nukeD8', function() {
//  return gulp.src(['project/web/d8'])
//    //.pipe(chmod(777))
//    .pipe(vinylPaths(del));
//
//  //return gulp.src('')
//  //  .pipe(shell([
//  //    'chmod -R 777 project/web/d8 && rm -rf project/web/d8'
//  //  ]));
//});

// Need to nuke d7 directory before Drush making
//gulp.task('d7:chmod', function() {
//  return gulp.src('web/drupal/d7/**/*')
//    .pipe(chmod(777));
//});

//gulp.task('d7:clean', function(cb) {
//  del(['web/drupal/d7'], cb);
//});

// Drush make drupal and contrib modules
//gulp.task('d7:make', ['d7:clean'], function() {
//  return gulp.src('')
//    .pipe(
//      shell(['drush make build/d7-generate.make web/drupal/d7'])
//    );
//});

// Copy local settings.php to new local d7 site
//gulp.task('d7:customFiles', ['d7:make'], function() {
//  return gulp.src([
//      'build/dev/d7/**/*'
//    ]).pipe(
//      gulp.dest('web/drupal/d7/sites/')
//    );
//});

//// Full drupal install
//gulp.task('d7:install', ['d7:customFiles'], function() {
//  return gulp.src('')
//    .pipe(
//      shell([
//        'echo "Installing drupal, make sure you catch the password printed out"',
//        'drush site-install standard --site-name=DOWNFALLD7 --yes',
//        'echo "Enabling downfall_migrate_feature"',
//        'drush en downfall_migrate_feature --yes',
//        'echo "Rebuilding node access permissons"',
//        'drush php-eval "node_access_rebuild();"',
//        'echo "Reverting features"',
//        'drush fr downfall_migrate_feature --yes',
//        'echo RUN SQL FROM FILE FOR forum_access',
//        "`drush sql-connect` < forum_access.sql"
//      ], {
//        'cwd':'web/drupal/d7/sites/d7.local.downfallguild.org'
//      })
//    );
//});

// Kick off d7 build
//gulp.task('d7:init', ['d7:install']);
//
//gulp.task('d7:cc', function() {
//  return gulp.src('')
//    .pipe(
//      shell(['drush cc all'], {'cwd': 'web/drupal/d7/sites/d7.local.downfallguild.org'})
//    );
//});

//gulp.task('d7:watch', function() {
//    watch(['build/dev/d7/**/*']).pipe(
//      shell(['rsync -vzr /var/www/df/build/dev/d7/* /var/www/df/web/drupal/d7/sites'])
//    );
//    //.pipe(gulp.dest('web/drupal/d7/sites/'));
//    //.pipe(shell(['rsync -vzr /var/www/df/build/dev/d7/* /var/www/df/web/drupal/d7/sites']));
//});



