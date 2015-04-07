/***********************************************************
     Starter code for Assignment 3

     This code was originally written by Jack Wang for
		    CSC418, SPRING 2005

		implements scene_object.h

***********************************************************/

#include <cmath>
#include <iostream>
#include "scene_object.h"

bool UnitSquare::intersect( Ray3D& ray, const Matrix4x4& worldToModel,
		const Matrix4x4& modelToWorld ) {
	// TODO: implement intersection code for UnitSquare, which is
	// defined on the xy-plane, with vertices (0.5, 0.5, 0), 
	// (-0.5, 0.5, 0), (-0.5, -0.5, 0), (0.5, -0.5, 0), and normal
	// (0, 0, 1).
	//
	// Your goal here is to fill ray.intersection with correct values
	// should an intersection occur.  This includes intersection.point, 
	// intersection.normal, intersection.none, intersection.t_value.   
	//
	// HINT: Remember to first transform the ray into object space  
	// to simplify the intersection test.

        Point3D rayOriginToModel = worldToModel * ray.origin;
        Vector3D rayDirToModel = worldToModel * ray.dir;
        
        // define a vertex and a normal
        Point3D vertex(0.5, 0.5, 0);
        Vector3D normal(0, 0, 1);
        
        //t
        double t = normal.dot(vertex - rayOriginToModel) / normal.dot(rayDirToModel);
        
        // "behind" the eye
        if (t <= 0) {
            return false;
        }
        
        // point p is an intersection
        Point3D p = rayOriginToModel + t * rayDirToModel;
        
        // verify that p falls within square
        if ((p[0] >= -0.5 && p[0] <= 0.5) && (p[1] >= -0.5 && p[1] <= 0.5)) {
            if (ray.intersection.none || ray.intersection.t_value > t) {
                ray.intersection.point = modelToWorld * p;
                ray.intersection.normal = worldToModel.transpose() * normal;
                ray.intersection.normal.normalize();
                ray.intersection.none = false;
                ray.intersection.t_value = t;
            
                return true;
            }
        }
    
	return false;
}

bool UnitSphere::intersect( Ray3D& ray, const Matrix4x4& worldToModel,
		const Matrix4x4& modelToWorld ) {
	// TODO: implement intersection code for UnitSphere, which is centred 
	// on the origin.  
	//
	// Your goal here is to fill ray.intersection with correct values
	// should an intersection occur.  This includes intersection.point, 
	// intersection.normal, intersection.none, intersection.t_value.   
	//
	// HINT: Remember to first transform the ray into object space  
	// to simplify the intersection test.
	
    
        Point3D origin(0,0,0);
        Point3D e = worldToModel * ray.origin;
        
        Vector3D e_vector(e[0], e[1], e[2]);
        
        
        Vector3D d = worldToModel * ray.dir;
        double d_dot = d.dot(d);
        double ed = e_vector.dot(d);
        double discriminant = 4 * ed*ed - 4 * d_dot * (e_vector.dot(e_vector) - 1);
        double t;
       
        if (discriminant > 0) {
            double t1 = (-2 * ed - sqrt(discriminant)) / (2 * d_dot);
            double t2 = (-2 * ed + sqrt(discriminant)) / (2 * d_dot);
        
            if (t1 > 0 && t2 > 0) {
                if (t1 > t2) {
                    t = t2;
                } else {
                    t = t1;
                }
            } else if (t1 > 0 && t2 < 0) {
                t = t1;
            } else if (t1 < 0 && t2 > 0) {
                t = t2;
            } else {
                ray.intersection.none = true;
                return false;
            }
        } else if (discriminant == 0) {
            double t = -ed / d_dot;
            if (t < 0) {
                ray.intersection.none = true;
                return false;
            }
        } else {
            ray.intersection.none = true;
            return false;
        }

        Point3D p = e + t * d;
        
        Vector3D norm(p[0], p[1], p[2]);
        norm.normalize();
        
        ray.intersection.point = modelToWorld * p;
        ray.intersection.normal = worldToModel.transpose() * norm;
        ray.intersection.normal.normalize();
        ray.intersection.none = false;
        ray.intersection.t_value = t;

        return true;
}

