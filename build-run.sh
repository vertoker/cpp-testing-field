# This script compile code using clang++
# First parameter $1 is must be file name (use Tab for auto complete)
# Other next parameters will be pasted as parameters for compiler

BaseDir="$(pwd)"
BuildDirectory="out/"
#echo $BaseDir

if [ -z $1 ]; then
  echo "Enter .cpp name as first parameter"
  exit 1
fi

# Ensure build directory is exists
if [ ! -d "$BaseDir/$BuildDirectory" ]; then
  echo "Create build directory at $BaseDir/$BuildDirectory"
  mkdir "$BaseDir/$BuildDirectory"
fi

CompilerArguments=""

for i in $@
do
  if [[ "$i" == "$1" ]]; then
    continue
  fi

  CompilerArguments="$CompilerArguments $i"
done

#echo "$CompilerArguments"

clang++ $CompilerArguments $1 --output="$BuildDirectory$1.out"

./"$BuildDirectory$1.out"

exit 0

