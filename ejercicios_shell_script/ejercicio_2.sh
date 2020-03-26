
#!/bin/zsh
# Jose Luiz Correa Junior | github -> juninhoojl
# Estoy utilizando Z shell en macOS 10.15.3

# Por lo menos dos argumentos
if [ $# != 3 ]; then
  	echo "Son necessarios 3 argumentos"
    exit 1
fi

case $2 in
	'+')
		echo "Suma = `expr $1 + $3`"
		;;
	'-')
		echo "Subtracion = `expr $1 - $3`"
		break
		;;
	'M')
		echo "Multiplicacion = `expr $1 \* $3`"
		break
		;;
	'D')
		echo "Division = `expr $1 / $3`"
		break
		;;
	*)
		echo "Operacion invalida"
		;;
  esac

