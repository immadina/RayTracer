/***********************************************************
     Starter code for Assignment 3

     This code was originally written by Jack Wang for
		    CSC418, SPRING 2005

		implements light_source.h

***********************************************************/

#include <cmath>
#include "light_source.h"

void PointLight::shade( Ray3D& ray ) {
	// TODO: implement this function to fill in values for ray.col 
	// using phong shading.  Make sure your vectors are normalized, and
	// clamp colour values to 1.0.
	//
	// It is assumed at this point that the intersection information in ray 
	// is available.  So be sure that traverseScene() is called on the ray 
	// before this function.  

    
        Point3D p = ray.intersection.point;
        
        Vector3D normal = ray.intersection.normal;
        normal.normalize();
        
        //Point3D ray_origin = ray.origin;
        
        Vector3D ray_dir = ray.dir;
        ray_dir.normalize();
        
        Vector3D light_dir = _pos - p;
        light_dir.normalize();
        
        //Vector3D r = light_dir - 2 * (normal.dot(light_dir)) * normal;
        
       
        //r.normalize();
        Vector3D r = operator -(light_dir, ray_dir);
        double len = sqrt(r.dot(r));
        r = operator *(1/len, r);
        r.normalize();
        
        Material* mat = ray.intersection.mat;
        Colour d = fmax(0, normal.dot(light_dir)) * mat->diffuse * _col_diffuse;
        Colour s = pow(fmax(0, normal.dot(r)), mat->specular_exp) * mat->specular * _col_specular;
        Colour a = mat->ambient * _col_ambient;
        
        
        ray.col = a + d + s;
        ray.col.clamp();
        
}

