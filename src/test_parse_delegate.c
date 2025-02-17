// //main for testing parse delegate only
// #include "../inc/miniRT.h"

// /*tests parse_ambient and displays a message if the result (success / failure) is unexpected*/
// void test_ambient(void)
// {
// 	char *valid_ambient_low = "A 0.0 0,0,0";
// 	char *valid_ambient_middle = "A 0.5 128,128,128";
// 	char *valid_ambient_high = "A 1.0 255,255,255";
	
// 	char *invalid_ambient = "A 1.5 255,255,255"; // Ambient ratio out of range
// 	char *invalid_ambient_format = "A 0.5 255-255-255"; // Wrong separator
// 	char *invalid_missing_seperator = "A 0.5255-255-255 a"; // Wrong separator
	
// 	if (parse_delegate(valid_ambient_low) != SUCCESS) printf("Failed test valid_ambient_low\n");
// 	if (parse_delegate(valid_ambient_middle) != SUCCESS) printf("Failed test valid_ambient_middle\n");
// 	if (parse_delegate(valid_ambient_high) != SUCCESS) printf("Failed test valid_ambient_high\n");
	
// 	if (parse_delegate(invalid_ambient) != 1) printf("Failed test invalid_ambient\n");
// 	if (parse_delegate(invalid_ambient_format) != 1) printf("Failed test invalid_ambient_format\n");
// 	if (parse_delegate(invalid_missing_seperator) != 1) printf("Failed test invalid_missing_seperator\n");
// }

// void test_camera(void)
// {
// 	char *valid_camera_low = "C -1000,-1000,-1000 -1,-1,-1 0";
// 	char *valid_camera_middle = "C 0,0,0 0,0,0 90";
// 	char *valid_camera_high = "C 1000,1000,1000 1,1,1 180";
	
// 	char *invalid_camera = "C -50.0,0,20 0,0,2 70"; // Orientation out of range
// 	char *invalid_camera_fov = "C -50.0,0,20 0,0,1 190"; // FOV out of range
	
// 	if (parse_delegate(valid_camera_low) != 0) printf("Failed test valid_camera_low\n");
// 	if (parse_delegate(valid_camera_middle) != 0) printf("Failed test valid_camera_middle\n");
// 	if (parse_delegate(valid_camera_high) != 0) printf("Failed test valid_camera_high\n");
	
// 	if (parse_delegate(invalid_camera) != 1) printf("Failed test invalid_camera\n");
// 	if (parse_delegate(invalid_camera_fov) != 1) printf("Failed test invalid_camera_fov\n");
// }

// void test_light(void)
// {
// 	char *valid_light_low = "L -1000,-1000,-1000 0.0 0,0,0";
// 	char *valid_light_middle = "L 0,0,0 0.5 128,128,128";
// 	char *valid_light_high = "L 1000,1000,1000 1.0 255,255,255";
	
// 	char *invalid_light = "L -40.0,50.0,0.0 1.5 255,255,255"; // Brightness out of range
// 	char *invalid_light_rgb = "L -40.0,50.0,0.0 0.6 300,0,255"; // RGB out of range
	
// 	if (parse_delegate(valid_light_low) != 0) printf("Failed test valid_light_low\n");
// 	if (parse_delegate(valid_light_middle) != 0) printf("Failed test valid_light_middle\n");
// 	if (parse_delegate(valid_light_high) != 0) printf("Failed test valid_light_high\n");
	
// 	if (parse_delegate(invalid_light) != 1) printf("Failed test invalid_light\n");
// 	if (parse_delegate(invalid_light_rgb) != 1) printf("Failed test invalid_light_rgb\n");
// }

// void test_sphere(void)
// {
// 	char *valid_sphere_low = "sp -1000,-1000,-1000 0.1 0,0,0";
// 	char *valid_sphere_middle = "sp 0,0,0 50 128,128,128";
// 	char *valid_sphere_high = "sp 1000,1000,1000 100 255,255,255";
	
// 	char *invalid_sphere = "sp 0.0,0.0,20.6 -12.6 10,0,255";// Negative diameter
// 	char *invalid_sphere_format = "sp 0.0,0.0 20.6 12.6 10,0,255";// Missing comma
	
// 	if (parse_delegate(valid_sphere_low) != 0) printf("Failed test valid_sphere_low\n");
// 	if (parse_delegate(valid_sphere_middle) != 0) printf("Failed test valid_sphere_middle\n");
// 	if (parse_delegate(valid_sphere_high) != 0) printf("Failed test valid_sphere_high\n");
	
// 	if (parse_delegate(invalid_sphere) != 1) printf("Failed test invalid_sphere\n");
// 	if (parse_delegate(invalid_sphere_format) != 1) printf("Failed test invalid_sphere_format\n");
// }

// void test_plane(void)
// {
//     char *valid_plane_low = "pl -1000,-1000,-1000 -1,-1,-1 0,0,0";
//     char *valid_plane_middle = "pl 0.0,0.0,-10.0 0.0,1.0,0.0 128,128,128";
//     char *valid_plane_high = "pl 1000,1000,1000 1,1,1 255,255,255";
    
//     char *invalid_plane_normal = "pl 0.0,0.0,-10.0 0.0,2.0,0.0 0,0,225"; // Normal vector out of range
//     char *invalid_plane_format = "pl 0.0,0.0,-10.0 0.0,1.0,0.0, 0,0,225"; // Extra comma
    
//     if (parse_delegate(valid_plane_low) != 0) printf("Failed test valid_plane_low\n");
//     if (parse_delegate(valid_plane_middle) != 0) printf("Failed test valid_plane_middle\n");
//     if (parse_delegate(valid_plane_high) != 0) printf("Failed test valid_plane_high\n");
    
//     if (parse_delegate(invalid_plane_normal) != 1) printf("Failed test invalid_plane_normal\n");
//     if (parse_delegate(invalid_plane_format) != 1) printf("Failed test invalid_plane_format\n");
// }

// void test_cylinder(void)
// {
//     char *valid_cylinder_low = "cy -1000,-1000,-1000 -1,-1,-1 0.1 0.1 0,0,0";
//     char *valid_cylinder_middle = "cy 50.0,0.0,20.6 0.0,0.0,1.0 14.2 21.42 128,128,128";
//     char *valid_cylinder_high = "cy 1000,1000,1000 1,1,1 100 200 255,255,255";
    
//     char *invalid_cylinder_vector = "cy 50.0,0.0,20.6 0.0,0.0,2.0 14.2 21.42 10,0,255"; // Axis vector out of range
//     char *invalid_cylinder_diameter = "cy 50.0,0.0,20.6 0.0,0.0,1.0 -14.2 21.42 10,0,255"; // Negative diameter
//     char *invalid_cylinder_rgb = "cy 50.0,0.0,20.6 0.0,0.0,1.0 14.2 21.42 300,0,255"; // RGB out of range
    
//     if (parse_delegate(valid_cylinder_low) != 0) printf("Failed test valid_cylinder_low\n");
//     if (parse_delegate(valid_cylinder_middle) != 0) printf("Failed test valid_cylinder_middle\n");
//     if (parse_delegate(valid_cylinder_high) != 0) printf("Failed test valid_cylinder_high\n");
    
//     if (parse_delegate(invalid_cylinder_vector) != 1) printf("Failed test invalid_cylinder_vector\n");
//     if (parse_delegate(invalid_cylinder_diameter) != 1) printf("Failed test invalid_cylinder_diameter\n");
//     if (parse_delegate(invalid_cylinder_rgb) != 1) printf("Failed test invalid_cylinder_rgb\n");
// }

// int main(void)
// {
// 	// test_ambient();
// 	// test_camera();
// 	// test_light();
// 	test_sphere();
// 	test_plane();
// 	test_cylinder();
	
// 	//General invalid cases
// 	char *invalid_identifier = "X 0.2 255,255,255"; // Unknown identifier
// 	if (parse_delegate(invalid_identifier) != 1) printf("Failed test invalid_identifier\n");
	
// 	return 0;
// }