
#ifndef TMAT_H
#define TMAT_H

#define CA
    #include "cab.h"
#ifndef CA
    #include <string.h>
    #include <iostream>
    #include <stdlib.h>
    #include <assert.h>
    using namespace std;
#endif
typedef unsigned int uint;


template <class t>
class TMat
{
public:
	class dim
	{
	public:
		uint    fi = 0, co = 0, tam = 0;
		dim(){}
		bool	operator == (const dim &);
		void	operator =  (const dim &);
	};
	TMat()  {}
    TMat(uint f,uint c)				{ crear(f, c); }
    TMat(uint f,uint c,const t sc)	{ crear(f, c);escalar(sc); }
	TMat(TMat<t> & mat)				{ *this = mat; }
	TMat(const dim & d)				{ crear(d); }
	TMat(uint f, uint c, t*m)		{ copiar_ar(f, c, m); }
    ~TMat() {borrar();}
	dim & tam(){ return di;}
    //__________________
    void    mostrar(ostream & os = cout);
    void    escalar(const t);
    //__________________
    void    unos    (const uint);
    void    unos    (const uint,const uint);
    void    ceros   (const uint);
    void    ceros   (const uint,const uint);
    //__________________
	uint	fil()	{ return di.fi; }
	uint	col()	{ return di.co; }
	uint	fc()	{ return di.tam; }
	//__________________
    t *			operator[] (const uint);
    TMat<t> &	operator = (TMat<t> &);
    //__________________
private:
	dim di;
	t    ** data = nullptr;
	void    crear(uint, uint);
	void    crear(const dim &);
	void    borrar();
	void	copiar_ar(uint f, uint c,const t*m);
};

template <class t> bool TMat<t>::dim::operator==(const dim & d)
{
	return fi == d.fi && co == d.co;
}
template <class t> void TMat<t>::dim::operator=(const dim & d)
{
	fi = d.fi; co = d.co; tam = d.tam;
}

//------------------------------------
template <class t> static inline t ** crear_mat(uint f, uint c)
{
	t** data = new t*[f];
	data[0]  = new t[f*c];
	for (uint i = 1; i<f; i++)
		data[i] = data[i - 1] + c;
	return data;
}

template <class t> void TMat<t>::crear(uint f,uint c)
{
	if(data)borrar();
	di.fi = f; di.co = c; di.tam = f*c;
	data = crear_mat<t>(f, c);

}
template <class t> void TMat<t>::crear(const dim & d)
{
	if (data)borrar();
	di	 = d;
	data = crear_mat<t>(di.fi, di.co);
}
template <class t> void TMat<t>::borrar()
{
    if(data)
    {
        delete []data[0];
        delete []data;
		di.tam = di.fi = di.co = 0;
    }
}
template <class t> void TMat<t>::copiar_ar(uint f, uint c,const  t*m)
{
	assert(m);
	crear(f, c);
	for (uint i = 0; i < di.tam; i++)
		data[0][i] = m[i];
}
//---------------------------------------
//---------------------------------------

template <class t> void TMat<t>::mostrar(ostream & os= cout)
{
    for(uint i=0; i<di.fi; i++)
    {
		for (uint j = 0; j<di.co; j++)
            os<<data[i][j]<<"\t";
        os<<endl;
    }
    os<<endl;
}
//------------------------------------

template <class t> void TMat<t>::escalar(const t s)
{
	for (uint i = 0; i<di.tam; i++)
        data[0][i] = s;

}
//------------------------------------
template <class t> void TMat<t>::unos(const uint d)
{
    crear(d,d);
    escalar(1);
}
template <class t> void TMat<t>::unos(const uint d1,const uint d2)
{
    crear(d1,d2);
    escalar(1);
}
template <class t> void TMat<t>::ceros(const uint d)
{
    crear(d,d);
	memset(data[0], 0, di.fi*di.co*sizeof(t));
}
template <class t> void TMat<t>::ceros(const uint d1,const uint d2)
{
    crear(d1,d2);
	memset(data[0], 0, di.fi*di.co*sizeof(t));
}
//-------------------------------------
template <class t> t * TMat<t>::operator [](const uint d1)
{
    return data[d1];
}
template <class t> TMat<t> & TMat<t>::operator = (TMat<t> & mat)
{
	if(this != &mat)
    {
		crear(mat.tam());
        memcpy(*data,*mat.data,di.tam*sizeof(t));
    }
	return *this;
}

//--------------------------------------
template <class t>  TMat<t> operator + (TMat<t> &mat, TMat<t> &mat2)
{
	assert( mat.tam()==mat2.tam() );
    TMat<t>  res(mat.tam());
    for(uint i=0; i<res.fc(); i++)
        res[0][i] = mat[0][i] + mat2[0][i];
	return res;
}
template <class t>  TMat<t> operator * (TMat<t> &mat, TMat<t> &mat2)
{
	assert( mat.col() == mat2.fil() );
	TMat<t>  res;
	res.ceros(mat.fil(), mat2.col());
	for (uint i = 0; i < mat.fil(); i++)
		for (uint j = 0; j < mat2.col(); j++)
			for (uint k = 0; k < mat.col(); k++)
				res[i][j] += mat[i][k] * mat2[k][j];
	return res;
}


#endif // TMAT_H
