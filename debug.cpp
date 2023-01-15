//=================================================================
/// \file       debug.cpp
/// \brief      Debugging info
/// \author     David Kharabadze
/// \version    16237a
/// \copyright  GNU General Public License v.3
//=================================================================
//   ! " # $ % & ' ( ) * + , - . / 0 1 2 3 4 5 6 7 8 9 : ; < = > ?
// @ A B C D E F G H I J K L M N O P Q R S T U V W X Y Z [ \ ] ^ _
// ' a b c d e f g h i j k l m n o p q r s t u v w x y z { | } ~
//=================================================================

#include"debug.h"
void tDebug::print(const char *string){
	if(debug_file)
		fprintf(debug_file,string);
	fflush(debug_file);
	return;
};
void tDebug::print1(const char *string,int a){
	if(debug_file)
		fprintf(debug_file,string,a);
	fflush(debug_file);
	return;
};
void tDebug::print2(const char *string,int a,int b){
	if(debug_file)
		fprintf(debug_file,string,a,b);
	fflush(debug_file);
	return;
};
void tDebug::error(int line_number, const char *file_name){
	if (debug_file)
		fprintf(debug_file, "Error in line %i of file %s\n",
				line_number, file_name);
	fflush(debug_file);
	return;
}
tDebug::tDebug(void){
	debug_file=fopen("debug.txt", "rb");
	if(debug_file){
		fclose(debug_file);
		debug_file=fopen("debug.txt", "wt");
		fprintf(debug_file, "Start DEBUG\n");
		fflush(debug_file);
	}
};
tDebug::~tDebug(void){
	if(debug_file){
		fprintf(debug_file, "Finish DEBUG\n");
		fclose(debug_file);
	}
};

tDebug Debug;
