# This script compile code, using clang++ and most common parameters
# First parameter $1 is must be file name (use Tab for auto complete)
# Other next parameters will be pasted as parameters for compiler

BaseDir="$(pwd)"
BuildDirectory="build/"
#echo $BaseDir

if [ -z $1 ]; then
  echo "Enter .cpp name as first parameter"
  exit 1
fi

# Ensure build directory is exists
if [ ! -d "$BaseDir" ]; then
  mkdir "$BaseDir/$BuildDirectory"
fi


