# Copy SDL bin files to the root directory

BASEDIR=$(dirname $0)
if [ $BASEDIR == "." ]
then
    cp bin/*.dll ..
else
    cp QT-Utilites/bin/*.dll .
fi