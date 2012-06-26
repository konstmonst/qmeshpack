#pragma once
#include <QImage>
#include "mesh.h"

class ImageRegion;
class Image
{    

public:

    enum Mode
    {
        Top = 0,
        Bottom
    };

	typedef float ColorType;

	static bool minValue(ColorType imageZ, ColorType newZ);
	static bool maxValue(ColorType imageZ, ColorType newZ);

	Image(const Mesh &mesh, Mode mode, unsigned dilationValue = 0);
	Image(unsigned width, unsigned height);
	Image(unsigned width, unsigned height, ColorType clearColor);
    ~Image();

	unsigned	getWidth() const { return _width; }
	unsigned	getHeight() const { return _height; }
	QImage		toQImage() const;
	void		clear(ColorType value = 0.);
	ColorType	at(unsigned x, unsigned y) const { return _data[y * _width + x]; }
	void		setPixel(unsigned x, unsigned y, ColorType pixel);	
	bool		pixelIsInside(int x, int y);
	void		addBorder(unsigned borderSize, ColorType defaultValue);
	ColorType	maxColor() const { return _maxColor; }
	ColorType	minColor() const { return _minColor; }
	ColorType	maxColor(unsigned x, unsigned y, unsigned w, unsigned h) const;
	ColorType	minColor(unsigned x, unsigned y, unsigned w, unsigned h) const;
	void		insertAt(unsigned x, unsigned y, unsigned z, const Image& other);
    float		computeMinZDistance(unsigned x, unsigned y, const Image &other) const;
	void		triangle(QVector3D fa, QVector3D fb, QVector3D fc, bool (&compare)(ColorType, ColorType));
	QString		getName() const { return _name; }
	void		recalcMinMax();
	void		dilate(int dilationValue, bool (&compare)(ColorType, ColorType));
	ImageRegion	select(unsigned x, unsigned y, unsigned width, unsigned height);
	Image*		operator-(const ImageRegion& imgregion);

private:

	void		updateMinMax(ColorType color);

	unsigned    _width;
	unsigned    _height;
	float*      _data;
	float       _minColor;
	float       _maxColor;
	QString		_name;

	friend class ImageRegion;
};

class ImageRegion
{
public:
	friend class Image;

	Image* operator+(const Image* other);

	unsigned x() const { return _x; }
	unsigned y() const { return _y; }
	unsigned getWidth() const { return _width; }
	unsigned getHeight() const { return _height; }
	Image::ColorType at(unsigned x, unsigned y) const { return _parent->at(x, y); }

private:


	const Image* _parent;
	unsigned _x, _y, _width, _height;

	ImageRegion(const Image* parent, unsigned x, unsigned y, unsigned width, unsigned height);
};

