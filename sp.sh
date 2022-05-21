#!/bin/bash

echo 'Developer: Andrey Gubaydullin'
echo '1. Displays a list of configured repositories, indicating those that are connected'
echo '2. Asks the user for the name of the repository from the list'
echo '3. If the specified repository is connected, it disconnects it' 
echo '4. If the specified repository is disconnected, connects it'
echo ''

repository_1='Amazon Linux 2 core repository'
repository_2='Amazon Linux 2 core repository - source packages'
repository_3='Amazon Linux 2 core repository - debuginfo packages'

function toogle {
  echo "$rep" 
  if [ "$rep" = 'enabled=0' ]
  then 
    yum-config-manager --enable "$1"
    echo "Status has been change to 'enabled'!"
  else
    yum-config-manager --disable "$1"
    echo "Status has been change to 'disabled'!"
  fi      
}

function error_input_handler {
  echo "Error! You should choose from (1 | 2 | 3)"  >/dev/stderr
}

function error_exit_handler {
  echo "Error! You should choose from (y/n)"  >/dev/stderr
}

function call_first {
  rep="$(grep -m 1 'enabled=' /etc/yum.repos.d/amzn2-core.repo)"
  toogle "$repository_1"
}

function call_second {
  rep="$(grep -m 2 'enabled=' /etc/yum.repos.d/amzn2-core.repo | tail -1)"
  toogle "$repository_2"
}

function call_third {
  rep="$(grep -m 3 'enabled=' /etc/yum.repos.d/amzn2-core.repo | tail -1)"
  toogle "$repository_3"
}

while true
 	do {
      yum repolist all
      while true
      do { 
        echo "All repositories"
        echo "1) $repository_1"
        echo "2) $repository_2"
        echo "3) $repository_3"
        echo "Select a repository: (1 | 2 | 3):"
        read cin
        case "$cin" in 
                "1") call_first; break;;
                "2") call_second; break;;
                "3") call_third; break;;
                *) error_select_handler ; 
        esac
      }
      done

      while true
      do {
        yum repolist all
        echo "Exit the program? (y/n)"
        read cin
        case "$cin" in 
                "Y" | "y") echo "Exiting the program"; exit 1;;
                "N" | "n") break;;
                *) error_exit_handler;; 
        esac
      }
      done
  }  
done