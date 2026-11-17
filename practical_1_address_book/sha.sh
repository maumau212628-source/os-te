#!/bin/bash

echo "Enter file name:"
read file

while true
do
    echo
    echo "1. Create Address Book"
    echo "2. Display Address Book"
    echo "3. Insert Record"
    echo "4. Delete Record"
    echo "5. Modify Record"
    echo "6. Exit"

    echo "Enter choice:"
    read ch


    case $ch in

    1)
        touch $file
        echo "Address Book Created"
        ;;


    2)
        cat $file
        ;;


    3)
        echo "Enter ID:"A
        read id

        echo "Enter Name:"
        read name

        echo "Enter Phone:"
        read phone

        echo "Enter City:"
        read city

        echo "$id $name $phone $city" >> $file

        echo "Record Added"
        ;;


    4)
        echo "Enter ID to delete:"
        read id

        grep -v "^$id" $file > temp
        mv temp $file

        echo "Record Deleted"
        ;;


    5)
        echo "Enter ID to modify:"
        read id

        grep -v "^$id" $file > temp
        mv temp $file


        echo "Enter New Name:"
        read name

        echo "Enter New Phone:"
        read phone

        echo "Enter New City:"
        read city


        echo "$id $name $phone $city" >> $file

        echo "Record Modified"
        ;;


    6)
        echo "Exit"
        break
        ;;


    *)
        echo "Wrong Choice"
        ;;

    esac

done
