#!/bin/bash

file="addressbook.txt"

while true
do
    echo ""
    echo "===== ADDRESS BOOK ====="
    echo "1. Create address book"
    echo "2. View address book"
    echo "3. Insert a record"
    echo "4. Delete a record"
    echo "5. Modify a record"
    echo "6. Exit"
    read -p "Enter your choice: " ch

    case $ch in
    1)
        read -p "Enter file name: " file
        touch "$file"
        echo "Address book created"
        ;;
    2)
        if [ -s "$file" ]
        then
            echo "ID,Name,Phone,Email"
            cat "$file"
        else
            echo "Address book is empty or does not exist"
        fi
        ;;
    3)
        read -p "Enter ID: " id
        read -p "Enter Name: " name
        read -p "Enter Phone: " phone
        read -p "Enter Email: " email
        echo "$id,$name,$phone,$email" >> "$file"
        echo "Record inserted"
        ;;
    4)
        read -p "Enter ID to delete: " id
        if grep -q "^$id," "$file"
        then
            sed -i "/^$id,/d" "$file"
            echo "Record deleted"
        else
            echo "Record not found"
        fi
        ;;
    5)
        read -p "Enter ID to modify: " id
        if grep -q "^$id," "$file"
        then
            read -p "Enter new Name: " name
            read -p "Enter new Phone: " phone
            read -p "Enter new Email: " email
            sed -i "s/^$id,.*/$id,$name,$phone,$email/" "$file"
            echo "Record modified"
        else
            echo "Record not found"
        fi
        ;;
    6)
        echo "Goodbye"
        break
        ;;
    *)
        echo "Invalid choice, try again"
        ;;
    esac
done
