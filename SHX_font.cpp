#include"SHX_font.h"

#include<memory.h>
#include<math.h>
#include <ctime>
#include <string.h>

#include"debug.h"

//--STAT-----------------------------------------------------------------------------------------------------------------
    void Stat_t::init_font(void){
        rez_space = 6;//default space
        rez_blank = 1;//default blank
        font_is_empty = true;
        init_sym();
        return;
    }
    void Stat_t::init_sym(void){
        sym_max_x = 0.0;
        sym_is_empty = true;
        return;
    }
    void Stat_t::add_line(double x1,double x2, double y1,double y2){
        //--- sumbol
        double bx = (x1>x2)?x1:x2;
        if(bx>sym_max_x)sym_max_x=bx;
        sym_is_empty = false;

        //--- font
        double by = (y1>y2)?y1:y2;
        if((font_is_empty)||(by>font_max_y))font_max_y=by;

        double sy = (y1<y2)?y1:y2;
        if((font_is_empty)||(sy<font_min_y))font_min_y=sy;

        font_is_empty = false;
        return;
    }
    void Stat_t::add_circ(double x1,double x2, double y1,double y2,double bulge){
        //--- sumbol
        double bx = (x1>x2)?x1:x2;
        if(bx>sym_max_x)sym_max_x=bx;
        sym_is_empty = false;

        //--- font
        double by = (y1>y2)?y1:y2;
        if((font_is_empty)||(by>font_max_y))font_max_y=by;

        double sy = (y1<y2)?y1:y2;
        if((font_is_empty)||(sy<font_min_y))font_min_y=sy;

        font_is_empty = false;
        return;
    }
    void Stat_t::finish_sym(double cx,double cy){
        double my_diff = cx-sym_max_x;
        if((!sym_is_empty)&&(my_diff>0)){//skip empty symbols
            font_mid_blank+=my_diff;
            font_symbols++;
        }
        return;
    }
    void Stat_t::process_space(double cx,double cy){
        rez_space=int(cx+0.999);
        if(rez_space<=0)rez_space=1;
        return;
    }
    void Stat_t::finish_font(void){
        if(font_symbols>0){
            font_mid_blank/=font_symbols;
            rez_blank=int(font_mid_blank+0.999);
        }

        if(!font_is_empty){
            double font_vert_size = font_max_y-font_min_y;
            rez_vert = int(font_vert_size*0.05 + 0.999);
        }
        if(rez_blank<=0)rez_blank=1;
        if(rez_vert<=0)rez_vert=1;
        return;
    }



//-----------------------------------------------------------------------------------------------------------------------


const int CP1251_table[128]={ //--- https://ru.wikipedia.org/wiki/Windows-1251
     0x402, 0x403,0x201A, 0x453,  0x201E,0x2026,0x2020,0x2021,  0x20AC,0x2030, 0x409,0x2039,   0x40A, 0x40C, 0x408, 0x40F,
     0x452,0x2018,0x2019,0x201C,  0x201D,0x2022,0x2013,0x2014,  (0xFD),0x2122, 0x459,0x203A,   0x45A, 0x45C, 0x458, 0x45F,
      0xA0, 0x40E, 0x45E, 0x408,    0xA4, 0x490,  0xA6,  0xA7,   0x401,  0xA9, 0x404, 0xAB,     0xAC,  0xAD,  0xAE, 0x407,
      0xB0,  0xB1, 0x406, 0x456,   0x491,  0xB5,  0xB6,  0xB7,   0x451,0x2116, 0x454, 0xBB,    0x458, 0x405, 0x455, 0x457,
     0x410, 0x411, 0x412, 0x413,   0x414, 0x415, 0x416, 0x417,   0x418, 0x419, 0x41A, 0x41B,   0x41C, 0x41D, 0x41E, 0x41F,
     0x420, 0x421, 0x422, 0x423,   0x424, 0x425, 0x426, 0x427,   0x428, 0x429, 0x42A, 0x42B,   0x42C, 0x42D, 0x42E, 0x42F,
     0x430, 0x431, 0x432, 0x433,   0x434, 0x435, 0x436, 0x437,   0x438, 0x439, 0x43A, 0x43B,   0x43C, 0x43D, 0x43E, 0x43F,
     0x440, 0x441, 0x442, 0x443,   0x444, 0x445, 0x446, 0x447,   0x448, 0x449, 0x44A, 0x44B,   0x44C, 0x44D, 0x44E, 0x44F,
};
const int CP866_table[128]={ //--- https://ru.wikipedia.org/wiki/CP866
     0x410, 0x411, 0x412, 0x413,   0x414, 0x415, 0x416, 0x417,   0x418, 0x419, 0x41A, 0x41B,   0x41C, 0x41D, 0x41E, 0x41F,
     0x420, 0x421, 0x422, 0x423,   0x424, 0x425, 0x426, 0x427,   0x428, 0x429, 0x42A, 0x42B,   0x42C, 0x42D, 0x42E, 0x42F,
     0x430, 0x431, 0x432, 0x433,   0x434, 0x435, 0x436, 0x437,   0x438, 0x439, 0x43A, 0x43B,   0x43C, 0x43D, 0x43E, 0x43F,
    0x2591,0x2592,0x2593,0x2502,  0x2524,0x2561,0x2562,0x2556,  0x2555,0x2563,0x2551,0x2557,  0x255D,0x255C,0x255B,0x2510,
    0x2514,0x2534,0x252C,0x251C,  0x2500,0x253C,0x255E,0x255F,  0x255A,0x2554,0x2569,0x2566,  0x2560,0x2550,0x256C,0x2567,
    0x2568,0x2564,0x2565,0x2559,  0x2558,0x2552,0x2553,0x256B,  0x256A,0x2518,0x250C,0x2588,  0x2584,0x258C,0x2590,0x2580,
     0x440, 0x441, 0x442, 0x443,   0x444, 0x445, 0x446, 0x447,   0x448, 0x449, 0x44A, 0x44B,   0x44C, 0x44D, 0x44E, 0x44F,
     0x401, 0x451, 0x404, 0x454,   0x407, 0x457, 0x40E, 0x45E,    0xB0,0x2219,  0xB7,0x221A,  0x2116,  0xA4,0x25A0,  0xA0
};


bool get_string(FILE *f,const char *s){
	char cc;
	const char *uk=s;
	bool good=true;
	int chars_got=0;
	while(*uk!=0){
		if(fread(&cc,1,1,f)!=1){
			good=false;
			break;
		}
		chars_got++;
		if(cc!=*uk){
			good=false;
			break;
		}
		uk++;
	}
	if(!good)fseek(f,-chars_got,SEEK_CUR);
	return good;
}

bool SHX_Font_t::load_font(char *file_name){
	Debug.print("\nLoading file:");
	Debug.print(file_name);
	Debug.print("...\n");
	FILE *f = fopen(file_name, "rb");
	if (f == 0){
		Debug.print("Can't load font file\n");
		return false;
	}
	bool shapes0=get_string(f,"AutoCAD-86 shapes 1.0\15\12");
	bool shapes0bad=get_string(f,"AutoCAD-86 shapes 1.0\12");
	bool shapes1=get_string(f,"AutoCAD-86 shapes 1.1\15\12");
	bool shapes = shapes0|shapes1|shapes0bad;
	bool big_font=get_string(f,"AutoCAD-86 bigfont 1.0\15\12");
	bool uni_font=get_string(f,"AutoCAD-86 unifont 1.0\15\12");
	if(!(shapes||big_font||uni_font))Debug.print("Can't read header\n");
	//FILE *log=fopen("font.log","wt");

	if(shapes){
		if(shapes0|shapes1)fseek(f,0x1c,SEEK_SET);
		else if(shapes0bad)fseek(f,0x1b,SEEK_SET);
		else;
		fread(&total_chars,1,2,f);
		Debug.print1("Total symbols: %i (SHAPES)\n", total_chars);
	}else if(uni_font){
		fseek(f,0x19,SEEK_SET);
		fread(&total_chars,1,2,f);
		Debug.print1("Total symbols: %i (UNIFONT)\n", total_chars);
	}else if(big_font){
		fseek(f,0x1b,SEEK_SET);
		fread(&total_chars,1,2,f);
		Debug.print1("Total symbols< %i (BIGFONT)\n", total_chars);
		fseek(f,0x23,SEEK_SET);
	}else Debug.print("Unknown header\n");
	symbol_desc = new SymbolDesc_t[total_chars];

	int real_sn=0;//Real symbol number
	for(int sn=0;sn<total_chars;sn++){
        int local_shape_number=0,local_used_bytes=0,local_offset_bytes=0;
		fread(&local_shape_number,1,2,f);
		fread(&local_used_bytes,1,2,f);
		if(big_font){
            local_shape_number|=local_shape_number<<16;
            local_shape_number>>=8;
            local_shape_number&=0xffff;
            fread(&local_offset_bytes,1,4,f);
        }

        if(local_used_bytes!=0){//Non-zero shapes
            symbol_desc[real_sn].shape_number=local_shape_number;
            symbol_desc[real_sn].used_bytes=local_used_bytes;
            symbol_desc[real_sn].offset_bytes=local_offset_bytes;
            symbol_desc[real_sn].data=new unsigned char[local_used_bytes];
            if(uni_font){//GET SHAPES "UNIFONT"
                fread(symbol_desc[real_sn].data,local_used_bytes,1,f);
            }

            //--- Print start
            int ccc = symbol_desc[real_sn].shape_number;
            if((ccc!=0)&&(ccc!=' ')&&(ccc!=13)&&(ccc!=10)&&(ccc<=255)){
                Debug.print1("%c",ccc);//fprintf(log," %c",c);
            }else{
                Debug.print1("<%04X>",ccc);
            }
            //Debug.print1("{%i}",symbol_desc[sn].used_bytes);
            if((real_sn%32==31)||(real_sn==(total_chars-1)))Debug.print("\n");
            //--- Print finish

            real_sn++;
        }
	}
	total_chars=real_sn;
	Debug.print1("Real chars = %i\n",total_chars);

	//font name
	//if(symbol_desc[0].shape_number==0){
		//for(int i=0;i<128;i++){
		//	fread(&font_name[i],1,1,f);
		//	if(font_name[i]==0)break;
		//}
	//}else return false;
	//symbol_desc[0].used_bytes=4;// size - strlen
	//fprintf(log, "Font name: %s\n", font_name);

	//GET SHAPES "SHAPES"
	if(shapes){
        for(int sn=0;sn<total_chars;sn++){
            if(symbol_desc[sn].used_bytes)
                fread(symbol_desc[sn].data,symbol_desc[sn].used_bytes,1,f);
        }
	}
	if(big_font){
        for(int sn=0;sn<total_chars;sn++){
            if(symbol_desc[sn].used_bytes){
                fseek(f,symbol_desc[sn].offset_bytes,SEEK_SET);
                fread(symbol_desc[sn].data,symbol_desc[sn].used_bytes,1,f);
            }
        }
	}
	/*
	if(symbol_desc[0].shape_number==0){
        int i=0;
        while(i<symbol_desc[0].used_bytes){
            font_name[i]=symbol_desc[0].data[i];
			if(font_name[i]==0)break;
			i++;
		}
        font_name[i]=0;
        Debug.print("<");
        Debug.print(font_name);
        Debug.print(">");
	}*/

	//get end
	if(!get_string(f,"EOF"))return false;

	//finish
	//fprintf(log,"LENGTH = %i\n",ftell(f));
	//fprintf(log,"Done!\n",ftell(f));
	fclose(f);
	font_is_loaded = true;

	//decode
	//fprintf(log,"File decoding...\n");
	if(symbol_desc[0].shape_number==0){
		//fprintf(log,"Above = %i, ",symbol_desc[0].data[0]);
		//fprintf(log,"Below = %i, ",symbol_desc[0].data[1]);
		//fprintf(log,"Modes = %i\n",symbol_desc[0].data[2]);
	}else return false;

	//decode-2
	for(int sn=0;sn<total_chars;sn++){
		SymbolDesc_t &sd=symbol_desc[sn];
		//fprintf(log,"%c)",sd.shape_number);
		int st=0;
		while(sd.data[st])st++;//Get text...
		st++;

		for(int i=st;i<sd.used_bytes;i++){
			//fprintf(log,"%i,",sd.data[i]);
		}
		//fprintf(log,"\n");
	}


	//fclose(log);
	return true;
}
int SHX_Font_t::convert_to_unicode(void){
    int strings[16];
    memset(strings,0,sizeof(strings));
    for(int i=0;i<total_chars;i++){
        int cn = symbol_desc[i].shape_number;
        int low  = cn&0x0f;
        int high = cn>>4;
        if(high<16)strings[high]|=1<<low;
    }
    bool CP866 =(strings[0x8]==0xffff)&&(strings[0x9]==0xffff)&&(strings[0xA]==0xffff)&&(strings[0xE]==0xffff);
    bool CP1251=(strings[0xC]==0xffff)&&(strings[0xD]==0xffff)&&(strings[0xE]==0xffff)&&(strings[0xF]==0xffff);
    //int encoding = (CP866)?(CP1251)?0xffff:866:(CP1251)?1251:0;
    int encoding = (CP1251)?1251:(CP866)?866:0;//cp1251 is "better"
    Debug.print1("Encoding = CP%i\n",encoding);
    for(int i=0;i<total_chars;i++){
        int cur_shape = symbol_desc[i].shape_number;
        if(cur_shape<128){;//ASCII
            symbol_desc[i].unicode_number=cur_shape;
        }else if(cur_shape<256){//Cyrilic CP1251 or CP866
            if(encoding==1251)
                symbol_desc[i].unicode_number=CP1251_table[cur_shape-128];
            else if(encoding==866)
                symbol_desc[i].unicode_number=CP866_table[cur_shape-128];
            else
                symbol_desc[i].unicode_number=cur_shape;
        }else{//Unicode
            symbol_desc[i].unicode_number=cur_shape;
        }
    }
    return encoding;
}

void SHX_Font_t::sort_symbols(void){
    for(int i=total_chars-1;i>0;i--){
        for(int j=0;j<i;j++){
            if(symbol_desc[j].unicode_number>symbol_desc[j+1].unicode_number){//change
                int temp0 = symbol_desc[j].unicode_number;
                symbol_desc[j].unicode_number=symbol_desc[j+1].unicode_number;
                symbol_desc[j+1].unicode_number=temp0;

                int temp1 = symbol_desc[j].shape_number;
                symbol_desc[j].shape_number=symbol_desc[j+1].shape_number;
                symbol_desc[j+1].shape_number=temp1;

                int temp2=symbol_desc[j].used_bytes;
                symbol_desc[j].used_bytes=symbol_desc[j+1].used_bytes;
                symbol_desc[j+1].used_bytes=temp2;

                unsigned char* temp3=symbol_desc[j].data;
                symbol_desc[j].data=symbol_desc[j+1].data;
                symbol_desc[j+1].data=temp3;
            }
        }
    }
}

void SHX_Font_t::print_shape(int cn){
    Debug.print1("PRINT <%04x>",cn);
    int sn=-1;
    for(int i=0;i<total_chars;i++){
        if(symbol_desc[i].shape_number==cn)sn=i;
    }
    if(sn<0){
        Debug.print("Unknown symbol\n");
        return;
    }
    Debug.print2("[%04x,%04x;",sn,symbol_desc[sn].unicode_number);
    Debug.print2("%04x,%04x]",(int)symbol_desc[sn].data,symbol_desc[sn].used_bytes);
    //symbol_desc[sn].offset_bytes
    for(int i=0;i<symbol_desc[sn].used_bytes;i++){
        Debug.print1("%02x,",symbol_desc[sn].data[i]);
    }
    Debug.print("..\n");
    return;
}

/*
void SHX_Font_t::decode_info(void){
    for(int sn=0;sn<total_chars;sn++){
        int shnum = symbol_desc[sn].shape_number;
        if(shnum ==0){
            int len = symbol_desc[sn].used_bytes;
            if(len){
                font_name = new char[++len];
                memset(font_name,0,len--);
                for(int cn=0;cn<len;cn++){
                    char cc = symbol_desc[sn].data[cn];
                    if(cc==0)break;
                    font_name[cn]=cc;
                }
                Debug.print(font_name);
                Debug.print("\n");
            }
        }
        if((shnum==0x0A)||(shnum==' ')){
            bool vert = (shnum==0x0A);
            bool horiz = (shnum==' ');
            int len = symbol_desc[sn].used_bytes;
            Debug.print((vert)?"Vertical:":"Horizontal");
            for(int bn=0;bn<len;bn++){
                Debug.print1("[%02x]",symbol_desc[sn].data[bn]);
            }
            Debug.print("\n");
        }
    }
    return;
}*/

void print_utf8(FILE *f,unsigned int unicode){
    if(unicode<=0x7f){//7 bit
        unsigned int byte1 = unicode;
        fprintf(f,"%c",byte1);
    }else if(unicode<0x7ff){//11 bit
        unsigned int byte1 = 0xc0 | 0x1f & (unicode>>6 );
        unsigned int byte2 = 0x80 | 0x3f & (unicode    );
        fprintf(f,"%c%c",byte1,byte2);
    }else if(unicode<0xffff){//16 bit
        unsigned int byte1 = 0xc0 | 0x0f & (unicode>>12);
        unsigned int byte2 = 0x80 | 0x3f & (unicode>>6 );
        unsigned int byte3 = 0x80 | 0x3f & (unicode    );
        fprintf(f,"%c%c%c",byte1,byte2,byte3);
    }else if(unicode<0x1fffff){//21 bit
        unsigned int byte1 = 0xc0 | 0x07 & (unicode>>18);
        unsigned int byte2 = 0x80 | 0x3f & (unicode>>12);
        unsigned int byte3 = 0x80 | 0x3f & (unicode>>6 );
        unsigned int byte4 = 0x80 | 0x3f & (unicode    );
        fprintf(f,"%c%c%c%c",byte1,byte2,byte3,byte4);
    }else ERR;
    return;
}

void SHX_Font_t::save_one_symbol(FILE *f,int sn,bool draw){
    pen_down=false;//true when drawing
    mult = 1.0;
    current_x=0.0;
    current_y=0.0;
    bool new_draw=draw;
    int unicode = symbol_desc[sn].unicode_number;
    if(unicode==0x20)new_draw=false;
    if(new_draw){
        fprintf(f,"[%04x] ",unicode);
        print_utf8(f,unicode);
        fprintf(f,"\n");
    }
    save_one_symbol_rrr(f,sn,new_draw,true);
    if(new_draw){
        fprintf(f,"\n");
    }
    return;
}

void SHX_Font_t::save_one_symbol_rrr(FILE *f,int sn,bool draw,bool init){
    unsigned char *symdata = symbol_desc[sn].data;
    int len=symbol_desc[sn].used_bytes;
    int poi=0;
    {//skip text data
        while((poi<len)&&(symdata[poi]!=0))poi++;
        poi++;
    }

	int stack_pointer=0;
	double stack_data[256];
	int prev_command = 0;//Previous command

	//--- Init vars
	mult = 1.0;
	//pen_down = false;
	line_started = false;
	if(init){
        current_x=current_y=0.0;
        pen_down = true;
    }

    while(1){
        if(poi>=len)break;//Cant override
        bool finish=false;
        unsigned int command=symdata[poi++];
        switch(command){
            case 0x0:{
                if(prev_command==0xE)break;
                if(line_started){
                    if(draw)fprintf(f,"\n");//finish line
                    line_started=false;
                }
                finish=true;
                break;
            }
            case 0x1:{
                if(prev_command==0xE)break;
                pen_down=true;
                break;//Draw on (pen down)
            }
            case 0x2:{
                if(prev_command==0xE)break;
                pen_down=false;
                break;//Draw off (pen up)
            }
            case 0x3:{//Divide
                if(poi>=len){finish=true;break;}
                if(prev_command==0xE){poi++;break;}
                mult/=symdata[poi++];
                break;
            }
            case 0x4:{//Multiply
                if(poi>=len){finish=true;break;}
                if(prev_command==0xE){poi++;break;}
                mult*=symdata[poi++];
                break;
            }
            case 0x5:{//Push to stack
                if(prev_command==0xE){break;}
                if(stack_pointer>=256){finish=true;break;}
				stack_data[stack_pointer++]=current_x;
				stack_data[stack_pointer++]=current_y;
				break;
            }
            case 0x6:{//Pop from stack
                if(prev_command==0xE){break;}
                if(stack_pointer<=0){finish=true;break;}
				current_y=stack_data[--stack_pointer];
				current_x=stack_data[--stack_pointer];
				//goto point
				break;
            }
            case 0x7:{//Subshape(!)
                //Debug.print1("!!!Subshape in <%04x>!!!\n",symbol_desc[sn].shape_number);
                if(poi>=len){finish=true;break;}
                if(prev_command==0xE){poi++;break;}
                int subshape=symdata[poi++];
                for(int i=0;i<total_chars;i++){
                    if(subshape==symbol_desc[i].shape_number){
                        save_one_symbol_rrr(f,i,draw,false);
                        break;
                    }
                }
                break;
            }
            case 0x8:{//goto/line (x,y)
                if((poi+1)>=len){finish=true;break;}
                if(prev_command==0xE){poi+=2;break;}
				double xx=(char)symdata[poi++];
				double yy=(char)symdata[poi++];
				xx*=mult;yy*=mult;
				double save_x=current_x,save_y=current_y;
				current_x+=xx;
				current_y+=yy;
				if(pen_down){
                    if(!line_started){
                        if(draw)fprintf(f,"%f,%f",save_x,save_y);
                        line_started=true;
                    }
                    if(draw)fprintf(f,";%f,%f",current_x,current_y);
                    stat.add_line(save_x,save_y,current_x,current_y);//STAT
				}else if(line_started){
                        if(draw)fprintf(f,"\n");//finish line
                        line_started=false;
				}
				break;
            }
            case 0x9:{//polyline
				while(1){
                    if((poi+1)>=len){finish=true;break;}
                    int xi = (char)symdata[poi++];
                    int yi = (char)symdata[poi++];
                    if((xi==0)&&(yi==0))break;
                    if(prev_command!=0xE){
                        double xx=xi, yy=yi;
                        xx*=mult;yy*=mult;
                        double save_x=current_x,save_y=current_y;
                        current_x+=xx;
                        current_y+=yy;
                        if(pen_down){
                            if(!line_started){
                                if(draw)fprintf(f,"%f,%f",save_x,save_y);
                                line_started=true;
                            }
                            if(draw)fprintf(f,";%f,%f",current_x,current_y);
                            stat.add_line(save_x,save_y,current_x,current_y);//STAT
                        }else if(line_started){
                            if(draw)fprintf(f,"\n");//finish line
                            line_started=false;
                        }
                    }
				}
				break;
            }
            case 0xA:{//circle (r,oct)
                if((poi+1)>=len){finish=true;break;}
                if(prev_command==0xE){poi+=2;break;}//!!!
				double r=(unsigned char)symdata[poi++];
				r*=mult;
				int octant=(char)symdata[poi++];
				bool clock_wize = (octant<0);
				int StartOctant=(octant>>4)&0x7;
				int OctantSpan=octant&0x7;
				if(clock_wize)OctantSpan=-OctantSpan;
                //Debug.print2("!!!0xA-circle(%i,%i)!!!",StartOctant,OctantSpan);

				//Calc bulge
			    double phi = OctantSpan*M_PI/8;
			    double bulge = 0.0;
			    if(OctantSpan!=0)
                    bulge=(1-cos(phi))/(sin(phi));

				//Draw circle
                double xx=2*r*cos((StartOctant+4)*M_PI/4);
                double yy=2*r*sin((StartOctant+4)*M_PI/4);
                if(OctantSpan!=0){
                    xx=r*(cos((StartOctant+OctantSpan)*M_PI/4)-cos(StartOctant*M_PI/4));
                    yy=r*(sin((StartOctant+OctantSpan)*M_PI/4)-sin(StartOctant*M_PI/4));
                }
                xx*=mult;yy*=mult;
                double save_x=current_x,save_y=current_y;
                current_x+=xx;
                current_y+=yy;
                if(pen_down){
                    if(!line_started){
                        if(draw)fprintf(f,"%f,%f",save_x,save_y);
                        line_started=true;
                    }
                    if(OctantSpan!=0){
                        if(draw)fprintf(f,";%f,%f",current_x,current_y);
                        if(draw)fprintf(f,",A%f",bulge);
                        stat.add_circ(save_x,save_y,current_x,current_y,bulge);//STAT
                    }else{
                        if(draw)fprintf(f,";%f,%f,A1.0",current_x,current_y);
                        if(draw)fprintf(f,";%f,%f,A1.0",save_x,save_y);
                        stat.add_circ(save_x,save_y,current_x,current_y,1.0);//STAT
                        stat.add_circ(current_x,current_y,save_x,save_y,1.0);//STAT
                    }
                }else if(line_started){
                        if(draw)fprintf(f,"\n");//finish line
                        line_started=false;
				}
				break;
            }
            case 0xB:{//fractional arc (start,finish,rh,rl,oct)
                //Debug.print1("!!!0xB-fractional arc in <%x>!!!",symbol_desc[sn].shape_number);
                if((poi+4)>=len){finish=true;break;}
                if(prev_command==0xE){poi+=5;break;}
				int start_offset = (unsigned char)symdata[poi++];
				int end_offset = (unsigned char)symdata[poi++];
				int rin =(unsigned char)symdata[poi++];
				(rin<<=8) |=(unsigned char)symdata[poi++];
				double r=rin*mult;
				int octant=(char)symdata[poi++];
				bool clock_wize = (octant<0);


				int StartOctant=(octant>>4)&0x7;
				int OctantSpan=octant&0x7;
				//=================================================
                    //See "Customizing Autocad 2009"
                    if(OctantSpan==0)OctantSpan=7;else OctantSpan--;
				//=================================================
				if (clock_wize)OctantSpan=-OctantSpan;
				int FinishOctant=StartOctant+OctantSpan;

				(StartOctant*=256)+=start_offset;
				(FinishOctant*=256)+=end_offset;
				//Debug.print2("S=%i,F=%i",StartOctant,FinishOctant);

				int arc_angle = FinishOctant-StartOctant;
				while(arc_angle<=-2048)arc_angle+=2048;//8*256
				while(arc_angle>=2048)arc_angle-=2048;//8*256
				if(( clock_wize)&&(arc_angle>0))arc_angle-=2048;
				if((!clock_wize)&&(arc_angle<0))arc_angle+=2048;

				bool full_circle=(arc_angle==0);

                double xx=-2*r*cos(StartOctant*M_PI/1024);
                double yy=-2*r*sin(StartOctant*M_PI/1024);
                if(!full_circle){
                    xx=r*(cos(FinishOctant*M_PI/1024)-cos(StartOctant*M_PI/1024));
                    yy=r*(sin(FinishOctant*M_PI/1024)-sin(StartOctant*M_PI/1024));
                }
                xx*=mult;yy*=mult;

                double save_x=current_x,save_y=current_y;
                current_x+=xx;
                current_y+=yy;


			    double bulge = 0.0;
			    if(!full_circle){
                    double phi = M_PI*arc_angle/2048.0;
                    bulge=(1-cos(phi))/(sin(phi));
                }

				//Draw circle
                if(pen_down){
                    if(!line_started){
                        if(draw)fprintf(f,"%f,%f",save_x,save_y);
                        line_started=true;
                    }
                    if(!full_circle){
                        if(draw)fprintf(f,";%f,%f",current_x,current_y);
                        if(draw)fprintf(f,",A%f",bulge);
                        stat.add_circ(save_x,save_y,current_x,current_y,bulge);//STAT
                    }else{
                        if(draw)fprintf(f,";%f,%f,A1.0",current_x,current_y);
                        if(draw)fprintf(f,";%f,%f,A1.0",save_x,save_y);
                        stat.add_circ(save_x,save_y,current_x,current_y,1.0);//STAT
                        stat.add_circ(current_x,current_y,save_x,save_y,1.0);//STAT
                    }
                }else if(line_started){
                        if(draw)fprintf(f,"\n");//finish line
                        line_started=false;
				}


				break;
            }
            case 0xC:{//Bulge arc (x,y,bulge)
                //Debug.print("!!!0xC-bulge arc(...)!!!");
                if((poi+2)>=len){finish=true;break;}
                if(prev_command==0xE){poi+=3;break;}
				double xx=(char)symdata[poi++];
				double yy=(char)symdata[poi++];
				xx*=mult;yy*=mult;
				int ibulge = (char)symdata[poi++];
				double bulge=ibulge;
				bulge*=1.0/127.0;//Bulge=Height/Displacement
                double save_x=current_x,save_y=current_y;
                current_x+=xx;
                current_y+=yy;
                if(pen_down){
                    if(!line_started){
                        if(draw)fprintf(f,"%f,%f",save_x,save_y);
                        line_started=true;
                    }
                    if(draw)fprintf(f,";%f,%f",current_x,current_y);
                    if(ibulge!=0){
                        if(draw)fprintf(f,",A%f",bulge);
                        stat.add_circ(save_x,save_y,current_x,current_y,bulge);//STAT
                    }else{
                        stat.add_line(save_x,save_y,current_x,current_y);//STAT
                    }
                }else if(line_started){
                        if(draw)fprintf(f,"\n");//finish line
                        line_started=false;
				}
                break;
            }
            case 0xD:{//PolyArc Bulge (x,y,bulge),..,(0,0)
                //Debug.print("!!!0xD - Poly arc bulge (...)!!!");
				while(1){
                    if((poi+1)>=len){finish=true;break;}
                    int xi = (char)symdata[poi++];
                    int yi = (char)symdata[poi++];
                    if((xi==0)&&(yi==0))break;//finish

                    if((poi)>=len){finish=true;break;}
                    int ibulge = (char)symdata[poi++];
                    double bulge = ibulge;
                    bulge*=1.0/127.0;//Bulge=Height/Displacement

                    if(prev_command!=0xE){
                        double xx=xi, yy=yi;
                        xx*=mult;yy*=mult;
                        double save_x=current_x,save_y=current_y;
                        current_x+=xx;
                        current_y+=yy;
                        if(pen_down){
                            if(!line_started){
                                if(draw)fprintf(f,"%f,%f",save_x,save_y);
                                line_started=true;
                            }
                            if(draw)fprintf(f,";%f,%f",current_x,current_y);
                            if(ibulge!=0){
                                if(draw)fprintf(f,",A%f",bulge);
                                stat.add_circ(save_x,save_y,current_x,current_y,bulge);//STAT
                            }else{
                                stat.add_line(save_x,save_y,current_x,current_y);//STAT
                            }
                        }else if(line_started){
                            if(draw)fprintf(f,"\n");//finish line
                            line_started=false;
                        }
                    }
				}
                break;
            }
            case 0xE:{//Vertical draw ignore
                break;
            }
            case 0xF:{//Vertical draw ignore
                Debug.print1("Unknown command 0F in symbol <%04x>\n",symbol_desc[sn].shape_number);
                break;
            }
            default:{//unit-lines :)
                //Debug.print2("Unknown command %02x in symbol <%04x>\n",command,symbol_desc[sn].shape_number);
                int l_length = (command>>4)&0xf;
                int l_direction = command & 0xf;
                int mmm[16][2]={
                    { 2, 0}, { 2, 1}, { 2, 2}, { 1, 2},
                    { 0, 2}, {-1, 2}, {-2, 2}, {-2, 1},
                    {-2, 0}, {-2,-1}, {-2,-2}, {-1,-2},
                    { 0,-2}, { 1,-2}, { 2,-2}, { 2,-1}
                };
                double xx = mmm[l_direction][0]*l_length*0.5;
                double yy = mmm[l_direction][1]*l_length*0.5;
   				xx*=mult;yy*=mult;

				double save_x=current_x,save_y=current_y;
				current_x+=xx;
				current_y+=yy;

				if(pen_down){
                    if(!line_started){
                        if(draw)fprintf(f,"%f,%f",save_x,save_y);
                        line_started=true;
                    }
                    if(draw)fprintf(f,";%f,%f",current_x,current_y);
                    stat.add_line(save_x,save_y,current_x,current_y);//STAT
				}else if(line_started){
                        if(draw)fprintf(f,"\n");//finish line
                        line_started=false;
				}


                break;
            }
        }
        prev_command=command;
        if(finish)break;
    }

    return;
}
bool SHX_Font_t::save_lff(char *file_name){
	FILE *f = fopen(file_name, "wt");
	if (f == 0){
		Debug.print("Can't load font file\n");
		return false;
	}

	for(int gstep=0;gstep<2;gstep++){
        //gstep=0 - test
        //gstep=1 - process
        if(gstep==1){//make header
            auto t = std::time(nullptr);
            auto tm = *std::localtime(&t);
            fprintf(f,"# Format:            LibreCAD Font 1\n");
            fprintf(f,"# Creator:           SHX2LFF converter\n");
            fprintf(f,"# Version:           1\n");
            fprintf(f,"# Name:              %s\n",font_name);
            fprintf(f,"# Encoding:          UTF-8\n");
            fprintf(f,"# LetterSpacing:     %i\n",stat.rez_blank);
            fprintf(f,"# WordSpacing:       %i\n",stat.rez_space);
            fprintf(f,"# LineSpacingFactor: %i\n",stat.rez_vert);
            fprintf(f,"# Created:           %04i-%02i-%02i\n",tm.tm_year+1900,tm.tm_mon+1,tm.tm_mday);
            fprintf(f,"# Last modified:     %04i-%02i-%02i\n",tm.tm_year+1900,tm.tm_mon+1,tm.tm_mday);
            fprintf(f,"# Author:            Unknown\n");
            fprintf(f,"# License:           Public domain (WTFPL,CC)\n");
            fprintf(f,"\n\n");//Two lines
        }

        stat.init_font();
        for(int sn=0;sn<total_chars;sn++){
            int shnum = symbol_desc[sn].shape_number;
            if((gstep==0)&&(shnum==0)){//Get info from zero
                int len = symbol_desc[sn].used_bytes;
                if(len){
                    font_name = new char[++len];
                    memset(font_name,0,len--);
                    for(int cn=0;cn<len;cn++){
                        char cc = symbol_desc[sn].data[cn];
                        if(cc==0)break;
                        font_name[cn]=cc;
                    }
                    int l2 = strlen(font_name);
                    if(l2==0){
                        if(font_name)delete[]font_name;
                        l2=strlen(file_name);
                        font_name=new char[l2+1];
                        strcpy(font_name,file_name);
                    }
                    Debug.print(font_name);
                    Debug.print("\n");
                }else{
                    int l2=strlen(file_name);
                    font_name=new char[l2+1];
                    strcpy(font_name,file_name);
                }
            }
            if(shnum==0x0)continue;//Skip 0x00
            if(shnum==0x0A)continue;//Skip 0x0A
            if(shnum==0x0D)continue;//Skip 0x0D
            if(symbol_desc[sn].used_bytes==0)continue;//Skip empty
            if(symbol_desc[sn].data==0)continue;//Skip empty

            //=== STARTDraw symbol
            //Debug.print2("{%04x-%04x}",symbol_desc[sn].shape_number,symbol_desc[sn].unicode_number);
            if(sn!=' ')stat.init_sym();
            save_one_symbol(f,sn,(gstep!=0));//!!!
            if(sn!=' ')stat.finish_sym(current_x,current_y);
            if(sn==' ')stat.process_space(current_x,current_y);
            //=== Finish draw symbol
        }
        stat.finish_font();

    }

 	fclose(f);
    return true;
}

void SHX_Font_t::free_memory(void){
    for(int sn=0;sn<total_chars;sn++){
        if(symbol_desc[sn].data!=0)
            delete[]symbol_desc[sn].data;
    }
    if(symbol_desc)
        delete[]symbol_desc;
    if(font_name)delete[]font_name;
    return;
}

SHX_Font_t::SHX_Font_t(void){
    memset(this,0,sizeof(*this));
    return;
}

SHX_Font_t::~SHX_Font_t(void){
    return;
}
