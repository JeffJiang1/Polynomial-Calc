#include <iostream>
#include <cmath>
#include "Polynomial.h"

// double *init_resize(poly_t &z, int &maxSize, int &minSize);
int maxDegree; 


void init_poly(poly_t &p, double const init_coeffs[], unsigned int const init_degree){
	if(p.a_coeffs != nullptr)		//checks if polynomial passed in has an address already, which means it was previously dynamically allocated array, if so delete it 
	{
		destroy_poly(p);
	}
	p.a_coeffs = new double[init_degree+1]; 	 
	//p.a_coeffs[init_degree]; 	// set the size of the array to be the degree
	
	for(std::size_t i{0}; i <= init_degree; i++){
		p.a_coeffs[i] = init_coeffs[i]; 	// copy contents from passed in array to new array(the one in struct)
	}

	p.degree = init_degree;
}

void destroy_poly (poly_t &p){
	delete [] p.a_coeffs;  // deallocate memory for array in the struct 
	p.a_coeffs = nullptr;  // assign it to nullptr 
}

unsigned int poly_degree(poly_t const &p){
	if(p.a_coeffs == nullptr){ 		// if array pointer is nullptr, empty array, so degree is 0
		return 0; 
	}
	else{
		return p.degree;  // return degree of polynomial 
	}
}

double poly_coeff(poly_t const &p, unsigned int n){
	if(p.a_coeffs == nullptr){  // if array pointer is nullptr, empty array, no coefficients 
		return 0; 
	} 
	else{ 		// get the coeff of degree n in the array 
		return p.a_coeffs[n]; 
	}
}

double poly_val(poly_t const &p, double const x){
	if(p.a_coeffs == nullptr){	// if array pointer is nullptr, empty array, no coefficients
		return 0; 
	}
	else{
		int n = p.degree + 1; 
		double result = p.a_coeffs[n];
		
		for( int i = p.degree; i >= 0; i--){
			result = result * x + p.a_coeffs[i]; 
		}
		return result; 
	}
}

void poly_add(poly_t &p, poly_t const &q){
	int sizeq = q.degree + 1; 
	int sizep = p.degree + 1; 
	if(p.a_coeffs == nullptr || q.a_coeffs == nullptr){
		throw 0; 
	}
	else if(p.degree >= q.degree){
		double *tmp = new double [sizep];
	
		for(int i = 0; i < sizep; i++){   // makes a new tmp array and copies q elements to it because q is const
			if(i >= sizeq){      //adds 0 to the array once all the q elements have been copied to match size of p array
				tmp[i] = 0; 		
			}
			else{
				tmp[i] = q.a_coeffs[i];    
			}
		}
		for(int i = 0; i < sizep; i++){
			p.a_coeffs[i] = p.a_coeffs[i] + tmp[i];   // adds content from tmp array to p array
			std::cout << p.a_coeffs[i] << std::endl; 
		}
		delete [] tmp;   // delete tmp array and set it to nullptr
		tmp = nullptr;
	}
	else{ //q.degree > p.degree
		double *tmp = new double [sizeq]; // new array that is size of q array
		
		for(int i = 0; i < sizeq; i++){
			if(i >= sizep){			// if its greater than p, add 0's to fill it
				tmp[i] = 0; 
			}
			else{
				tmp[i] = p.a_coeffs[i]; 	//copies contents from p array to tmp array
			}
		}
		for(int i = 0; i < sizeq; i++){
			tmp[i] = tmp[i] + q.a_coeffs[i];		// add q to tmp 
			std::cout << tmp[i] << std::endl;
		}
		
		p.degree = sizeq - 1; 			//resize the degree of p
		std::cout << p.degree;
		delete [] p.a_coeffs; 
		p.a_coeffs = tmp; 
	} 
}

void poly_subtract(poly_t &p, poly_t const &q){
	int sizep = p.degree + 1; 
	int sizeq = q.degree + 1; 
	if(p.a_coeffs == nullptr || q.a_coeffs == nullptr){
		throw 0; 
	}
	else if(p.degree >= q.degree){     
		double *tmp = new double [sizep]; 
		
		for(int i = 0; i < sizep; i++){  //since the size of p is >= q, we need to add 0 to match size of p array
			if(i >= sizeq){
				tmp[i] = 0; 
			}
			else{
				tmp[i] = q.a_coeffs[i];  //storing q elements in tmp array, and add 0's when needed
			}
		}
		
		for(int i = 0; i < sizep; i++){  	// subtract each q(tmp) value from p array 
			p.a_coeffs[i] = p.a_coeffs[i] - tmp[i]; 
			std::cout << p.a_coeffs[i] << std::endl; 
		}
		
		delete [] tmp;
		tmp = nullptr; 
	}
	else { //q.degree > p.degree
		double *tmp = new double [sizeq];
		
		for(int i = 0; i < sizeq; i++){
			if(i >= sizep){ 		// if i is greater than size of p array, add zeros to it 
				tmp[i] = 0;
			}
			else{
				tmp[i] = p.a_coeffs[i]; 	//set p = tmp
			}
		}
		
		for(int i = 0; i < sizeq; i++){
			tmp[i] = tmp[i] - q.a_coeffs[i];		// subtract q from tmp 
			std::cout << tmp[i] << std::endl;
		}
		
		p.degree = sizeq - 1; 		//set the degree to 1 less
		std::cout << p.degree << std::endl;
		
		delete [] p.a_coeffs; 
		p.a_coeffs = tmp;
	}
}

void poly_multiply(poly_t &p, poly_t const &q){
	int sizep = p.degree + 1; 
	int sizeq = q.degree + 1; 
	int sizetmp = p.degree + q.degree + 1;
	int i = 0;
	int j = 0;
	double *tmp = new double [sizetmp];
	if(p.a_coeffs == nullptr || q.a_coeffs == nullptr){
		throw 0; 
	}
	
	for(int i = 0; i < sizetmp; i++){ 		// allocate a new array with a larger size 
		tmp[i] = 0;  
	}

	for(int i = 0; i < sizep; i++){		// iterate through the p array 
		for(int j = 0; j < sizeq; j++){		// iterate through the q array
			tmp[i+j] = p.a_coeffs[i] * q.a_coeffs[j] + tmp[i+j];  // the p+q element stores the value 
		}
	}
	
	p.degree = sizetmp - 1; 
	delete [] p.a_coeffs; 
	p.a_coeffs = tmp;
}

double poly_divide(poly_t &p, double r){
	
	return 0; 
}

void poly_diff(poly_t &p){
	if(p.a_coeffs == nullptr){
		throw 0; 
	}
	
	int sizetmp = p.degree; 
	int sizep = p.degree + 1; 
	
	
	double *tmp = new double [sizetmp];
	
	if(p.degree = 0){
		tmp[0] = 0;
	}
	else{
		for(int i = 1; i < sizep; i++){
			tmp[i] = p.a_coeffs[i] * i; 
			std::cout << tmp[i] << std::endl;
		}		
	}
	
	
	p.degree = sizetmp - 1; 
	delete [] p.a_coeffs;
	p.a_coeffs = tmp;
}

double poly_approx_int(poly_t const &p, double a, double b, unsigned int n){
	return 0;
}

#ifndef MARMOSET_TESTING
int main();
#endif

#ifndef MARMOSET_TESTING
int main(){
	int degree = 4; 
	double array[degree]{3,4,2,3,1};
	poly_t my_poly{nullptr, 0};
	init_poly(my_poly, array, degree);
	
	int degree2 = 5; 
	double array2[degree]{1,2,3,4,23.4,234.3};
	poly_t my_poly2{nullptr, 0};
	init_poly(my_poly2, array2, degree2);
	
	poly_diff(my_poly);
}
#endif
