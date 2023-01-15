//=================================================================
/// \file       debug.h
/// \brief      Debugging info
/// \author     David Kharabadze
/// \version    16237a
/// \copyright  GNU General Public License v.3
//=================================================================
//   ! " # $ % & ' ( ) * + , - . / 0 1 2 3 4 5 6 7 8 9 : ; < = > ?
// @ A B C D E F G H I J K L M N O P Q R S T U V W X Y Z [ \ ] ^ _
// ' a b c d e f g h i j k l m n o p q r s t u v w x y z { | } ~
//=================================================================

#pragma once
#include<stdio.h>
struct tDebug{
	FILE *debug_file;
	void print(const char *string);
	void print1(const char *string,int a);
	void print2(const char *string,int a,int b);
	void error(int line_number,const char *file_name);
	tDebug(void);
	~tDebug(void);
};
extern tDebug Debug;
#define ERR Debug.error(__LINE__, __FILE__)

