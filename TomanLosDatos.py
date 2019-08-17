import sys
import serial
import time 

#creandoUnaFuncion para crear archivos


def creararchivo():
	archivo=open('DatosSinTransformar.txt','w')
	archivo.close()

def escribir(viene):
	archivo=open('DatosSinTransformar.txt','a')
	archivo.write(viene)

	
#crear el puerto serial donde lo voy a conectar el bluetooth
creararchivo()
import serial.tools.list_ports
ports = list(serial.tools.list_ports.comports())
for p in ports:
	print (p)

ser = serial.Serial(p[0],9600,timeout=0)

empezar=time.time()
while 1:
	
	time.sleep(0)
	info=ser.readline()
	diferencia= time.time()-empezar
	if diferencia > 120:
		break
	
	valor=info.decode('utf-8')

	if(info!=b''):
		print(info)


