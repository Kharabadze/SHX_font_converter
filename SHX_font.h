#pragma once
#include<stdio.h>

struct SymbolDesc_t{
	int shape_number;
	int unicode_number;
	int used_bytes;
	int offset_bytes;
	unsigned char *data;
};

struct Stat_t{
    int font_symbols;
    double font_max_y;
    double font_min_y;
    double font_mid_blank;
    double sym_max_x;
    bool sym_is_empty;
    bool font_is_empty;
    int rez_blank,rez_space,rez_vert;//Out
    void init_font(void);
    void init_sym(void);
    void add_line(double x1,double x2, double y1,double y2);
    void add_circ(double x1,double x2, double y1,double y2,double bulge);
    void finish_sym(double cx,double cy);
    void process_space(double cx,double cy);
    void finish_font(void);
};

struct SHX_Font_t{
	bool font_is_loaded;
	int total_chars;//!!!
	char *font_name;
	SymbolDesc_t *symbol_desc;

	//--- statistics
	Stat_t stat;

	//--- for draw
    bool pen_down=false;//true when drawing
    bool line_started = false;
    double mult = 1.0;//multiply coefficient
    double current_x=0.0,current_y=0.0;


	//--- font proc
	bool load_font(char *file_name);
	int convert_to_unicode(void);
	void sort_symbols(void);
	//void decode_info(void);
	void save_one_symbol(FILE *f,int sn,bool draw);
	void save_one_symbol_rrr(FILE *f,int sn,bool draw,bool init);
	bool save_lff(char *file_name);
	void free_memory(void);
	void print_shape(int cn);

/*	//--- graph part
	virtual void get_current_location(int *x,int *y);
	virtual void go_to(int x,int y);
	virtual void put_pixel(int x,int y);

	//--- output
	void fontlib_draw_line(double x, double y);
	void draw_char(int c);
	void draw_simple_string(const char *s);
	void draw_string(const char *s);
*/
	SHX_Font_t(void);
	~SHX_Font_t(void);
};


//==================================================== Ext. Data
//  https://en-academic.com/dic.nsf/enwiki/11038640
//  https://www.bricsys.com/blog/decoding-shapes-and-fonts-customizing-bricscad-p19
//  http://cadhouse.narod.ru/articles/acad/acad_shx_read.htm
//

