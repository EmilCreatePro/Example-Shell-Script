echo $0
echo Number of arguments $#

if [ $# -ne 1 ]; then echo Warning! Only one argument needed!; exit 1
fi

#if [ -f $1 ] ; then echo $1 is regular file; echo '' > $1
#    else echo $1 is NOT a regular file or it does not exist!; exit 2
if ! [ -f $1 ] || [ -h $1 ]; then echo $1 is NOT a regular file; exit 2
    else echo $1 is regular file; echo '' > $1
fi

while read line
do
    path=$line
    if [ $path = Gata ]; then break
    fi

    if [ -d $path ]; then echo $path e director!; 

        
        nr=`ls -l $path | grep '^[-]' | wc -l`

        echo Avem $nr fisiere obisnuite

        for i in $path/*
        do
            echo $i
            if [ -L $i ]; then
                if [[ $i =~ s$ ]]
                then
                    echo $i is a simbolic link with suffix s
                    echo $i >> $1
                fi 
            fi
        done
    fi
done

echo DONE