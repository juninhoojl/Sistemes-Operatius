#!/bin/zsh
# Jose Luiz Correa Junior | github -> juninhoojl
# Estoy utilizando Z shell en macOS 10.15.3

# Por lo menos dos argumentos
if [ $# != 2 ]; then
  	echo "Son necessarios 2 argumentos"
    exit 1
else

	# Fichero no existe
	if [ ! -f $1 ]; then
    	echo "$1 no existe"
    	exit 1
	fi

	# Si existe directorio borra contenido
	if [ -d $2 ]; then
		rm -rf $2/*
	else
		mkdir $2
	fi

	cp $1 cp_$1
	gzip cp_$1
	mv cp_$1* $2/
	exit 0

fi
