# The **Great** Drupal Migration

# Knowledge Required
 
 These instructions assume Novice-Level knowledge, simply in the interest of documenting each step of the installation. 

 Useful Knowlege
 * The Linux Shell
  * Its big, scary, and for those 'smart' geeks, but the Shell really is **not* all that scary. There's actually a great step-by-step instruction for learning it written at a 6th grade reading level:
  * [LinuxCommand.org](http://linuxcommand.org/](http://linuxcommand.org/ "LinuxCommand.org") - Great tutorial on routinely used shell commands for people not interested in actually learning UNIX.
  * [Unix Tutorial For Beginners](http://www.ee.surrey.ac.uk/Teaching/Unix/ "Unix Tutorial For Beginners")

# Software / Tools Required

 ## On Windows Machine (Your PC)
  1. [The Whole Git](https://git-scm.com/download/win "Git")
   1. Choose "Use Git and optional Unix tools from the Windows Command Prompt".
   2. Choose "Checkout Windows-style, commit Unix-style line endings."
   3. Enable Caching.
   4. [GitHub Desktop](https://desktop.github.com/ "GitHub Desktop") is also a fun tool.
  1. [HeidiSQL](http://www.heidisql.com/download.php "HeidiSQL")
  2. Text Editor / IDE 
   1. [atom.io](atom.io "atom.io"), [Sublime Text](http://www.sublimetext.com/2 "Sublime Text"), PHPStorm, etc.
  3. [Windows PowerShell](https://support.microsoft.com/en-us/kb/968929 "Windows PowerShell 2.0")
   1. There is a good instruction about using PowerShell alongside [Git for Windows](http://haacked.com/archive/2011/12/19/get-git-for-windows.aspx/ "Git for Windows").
  4. [Cmder](http://cmder.net/ "Cmder") or your choice of a good Terminal Emulator    
   1. Set Priviledges:
    1. After installing, find the .exe in the root folder.
    2. Right-click on the program and select 'Run as Administrator'.
  5. Install posh-git
    1. Execute Command in Cmder: 
	> Install-Module posh-git	
  6. Set up SymLinks
   + There are instructions [here](http://blog.puphpet.com/blog/2015/06/25/windows-symlinks/).
   + SymLinks have to be setup for drush make to function properly on the remote machine. 
   1. Download the [Polsedit - User Policies Editor](http://www.southsoftware.com/ Polsedit - User Policies Editor)
   2. Open the version for your machine. (Probably the x64, one would hope.)
   3. Double-click on 'Create symbolic links'.
   4. Select 'Add User or Group...'
   5. Find your user-name and double-click on it.
   6. 
   7. Close.
  7. [PuPHPet](https://puphpet.com/upload-config#frontpage "PuPHPet") \(In-Browser, no install required.\) 
   + "A simple GUI to set up virtual machines for Web development".
   + PuPHPet is an in-browser quick-click GUI for the [Vagrant Automation Tool](https://www.vagrantup.com/ "Vagrant") that removes all code-work. 
   + This is to make anyone who has every set up a virtual machine hate the world in general. It takes all of the work done and completely automates it to the nth degree using 
      
## On Vagrant Host (via ssh vagrant)
  1. npm install 
   + *node.js* Package Manager / Dependancy Manager
  2. [Drush](http://www.drush.org/en/master/ "Drush Docs")
   + Drush should auto-install during the initial *vagrant up*.
   + 
  3. 

# Commands to Know / Commands You Need

 * vagrant up
  - Turn vagrant on, downloading additional files to meet vagrant requirements as defined, if necessary. Removes necessity to transfer major gb sized servers by pulling configuration piles and packages directly from the Internet like Linux.
 * vagrant halt
  - Attempts to 'shut down' the created vagrant VMWare Server.
 * 

## Step 1: Administrator Privlidges 

Right-click on the chosen text-editor and cmd-prompt/terminal software (atom.io and Cmder, for example) and select 'Run as Administrator'. This ensures changes are made with sufficient privileges .


## Step 2: Editing the hosts file

You, as the User, should not have to do this. However, the hosts file should be edited via a trusted text-editor with 'Administrator' privlidges. 

By editing the hosts file (c:\windows\System32\drivers\etc\hosts), Users can add in default localhost information and ensure websearches for localhost run servers do not try and pull from the Internet.  

Basically, it re-directs internet searches for specific websites / IP Addresses back to your local computer so you can see local development *as* you develop it.

# Notes To-Be-Added

### Setting Up The Drupal Server (after vagrant up and vagrant ssh):
[06:27 AM]-[vagrant@local]-[/var/www/df]
$ rm -rf web/drupal/d8

[06:29 AM]-[vagrant@local]-[/var/www/df]
$ drush make build/d8-generate.make web/drupal/d8
