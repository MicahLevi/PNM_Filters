#ifndef FILTERS_H
#define FILTERS_H
#include <filter.h>



class Shrinker: public Filter
{
	public:
							Shrinker(void){};
		virtual void 		Execute(void);
		virtual const char* FilterName() {return "Shrinker";};
		virtual int			getNumInputs(void);
};

class LRConcat: public Filter
{
	public:
							LRConcat(void){};
		virtual void 		Execute(void);
		virtual const char* FilterName() {return ":LRConcat";};
};

class TBConcat: public Filter
{
	public:
							TBConcat(void){};
		virtual void 		Execute(void);
		virtual const char* FilterName() {return "TBConcat";};
};

class Blender: public Filter
{
	protected:
		float 				ratio;
	public:
							Blender(void){};
		void 				SetFactor(float f){ratio = f;};
		virtual void 		Execute(void);
		virtual const char	*FilterName() {return "Blender";};
};

class Transpose : public Filter
{
	protected:
		
	public:
							Transpose(void){};
		virtual void 		Execute(void);
		virtual int			getNumInputs(void);
		virtual const char	*FilterName() {return "Tanspose";};
};

class Invert : public Filter
{
	public:
							Invert(void){};
		virtual void 		Execute(void);
		virtual int			getNumInputs(void);
		virtual const char 	*FilterName() {return "Invert";};
};

class Crop : public Filter
{
	public:
							Crop()  { Istart = Istop = Jstart = Jstop = -1; };
		virtual const char 	*FilterName() { return "Crop"; };
		virtual void		Execute();
		virtual int			getNumInputs(void);
		void           		SetRegion(int Istart_, int Istop_, int Jstart_, int Jstop_)
				              {
				                Istart = Istart_;
				                Istop  = Istop_;
				                Jstart = Jstart_;
				                Jstop  = Jstop_;
				              }
	private:
  		int Istart, Istop, Jstart, Jstop;
};

class Checkerboard : public Filter
{
	public:
							Checkerboard(void){};
		virtual void 		Execute(void);
		virtual const char 	*FilterName() {return "Checkerboard";};
};


class Color: public Source
{
	protected:
		virtual const char	*SourceName(void){return "Color";};
		virtual void		Execute(void){};
	public:
							Color(int width, int height, int red, int green, int blue);
};


class CheckSum: public Sink
{
	public:
							CheckSum(void){};
		void 				OutputCheckSum(const char *);
		virtual const char 	*SinkName(void){return "CheckSum";};	
};
#endif








