

#ifndef _CCONT_H
#define _CCONT_H

class CCont
{
	public:
	string Name;
	string Title;

	float Weight;
	
	bool fl_const;
	
	float startVal;

	int Color;
	int FillStyle;
	CCont(){};
	CCont(string, int );
	CCont(string, string, int );
	CCont(string, string, float , int, int );
};

CCont::CCont(string name, int color)
{
	Name.assign(name);
	Title.assign(name);

	fl_const = false;
	startVal = 1.;

	Weight = 1;
	Color = color;
	FillStyle = 0;
};

CCont::CCont(string name, string title, int color)
{
	Name.assign(name);
	Title.assign(title);

	fl_const = false;
	startVal = 1.;

	Weight = 1;
	Color = color;
	FillStyle = 0;
};

CCont::CCont(string name, string title, float w, int color, int Fill)
{
	Name.assign(name);
	Title.assign(title);

	fl_const = false;
	startVal = 1.;

	Weight = w;
	Color = color;
	FillStyle = Fill;
};
#endif
