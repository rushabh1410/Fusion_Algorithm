# Operating System

This software has been tested under Windows Platform.

Windows family:
* Windows 7 (32-bit, 64-bit)
* Windows 8 (64-bit)
* Windows 10 (64-bit)

# Compilers

This software has been tested using the compiler:

* gcc (7.4.0)
* Probably it will work with previous versions as well.

# Dependencies

Following are the requirements to run this software:

* GNU Make
* GCC
* GSL(GNU Scientific Library)
* CUnit (Unit Testing Framework)

In order to install this package ,refer the Installation steps below.

# Installation

We had install all the required packages through cygwin terminal.

## Steps

1. Download the cygwin from https://cygwin.com/install.html
	>Download the 32-bit or 64-bit .exe depending on your device configuration.

2. Run the setup file. Click Next.

3. Choose "Install from internet" and select next.

4. Choose your preferred directory for storage of Cygwin files and click next.

5. Choose your preferred directory for storage of Cygwin local package directory and click next.
   Remember both these locations as they might be required for installing more libraries later.

6. Click next.You need to choose a mirror to download Cygwin. Choose any mirror and click next

7. Select the Packages now and latter on you can install the additional package as well.

8. Click on search box and look for following packages:
	* make (Under Devel )
	* gcc-core (Under Devel category)
	* libgsl-devel (Under Libs category)
	* gsl (Under Science category)
	* CUnit (Libs , Math)

9. Click on Next. All the packages along with its dependencies will be downloaded.

10. Cygwin can be operated in two ways:
	* Through Cygwin Terminal
	* Through Command Prompt

11. To use cygwin from command prompt, set the path of cygwin to path environment variable.
	> For instance, path looks like "C:\cygwin64\bin"

12. Check the installed dependencies through following command:
	* cygcheck -cd | grep <name_package>
	> For instance , it can be cygcheck -cd | grep gsl

13. Now , you are ready to use the software.

# Compile and Run the Project

Refer doc/user_guide.md file to build and run the software

