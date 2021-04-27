/**
 * @file cvms5.h
 * @brief Main header file for CVM-S5 library.
 * @author David Gill - SCEC <davidgil@usc.edu>
 * @version 1.0
 *
 * Delivers CVM-S5 which consists of Po Chen and En-Jui Lee's full 3D
 * tomographic results with a Vs30-based GTL as per Po Chen and Geoff Ely.
 *
 */

// Includes
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <math.h>

#include "etree.h"
#include "proj_api.h"

// Constants
#ifndef M_PI
	/** Defines pi */
	#define M_PI 3.14159265358979323846
#endif

/** Defines a return value of success */
#define SUCCESS 0
/** Defines a return value of failure */
#define FAIL 1

/* forward declaration */
void utm_geo_(double*, double*, double*, double*, int*, int*);

// Structures
/** Defines a point (latitude, longitude, and depth) in WGS84 format */
typedef struct cvms5_point_t {
	/** Longitude member of the point */
	double longitude;
	/** Latitude member of the point */
	double latitude;
	/** Depth member of the point */
	double depth;
} cvms5_point_t;

/** Defines the material properties this model will retrieve. */
typedef struct cvms5_properties_t {
	/** P-wave velocity in meters per second */
	double vp;
	/** S-wave velocity in meters per second */
	double vs;
	/** Density in g/m^3 */
	double rho;
	/** Qp */
	double qp;
	/** Qs */
	double qs;
} cvms5_properties_t;

/** The CVM-S5 configuration structure. */
typedef struct cvms5_configuration_t {
	/** The zone of UTM projection */
	int utm_zone;
	/** The model directory */
	char model_dir[128];
	/** GTL on or off (1 or 0) */
	int gtl;
	/** Number of x points */
	int nx;
	/** Number of y points */
	int ny;
	/** Number of z points */
	int nz;
	/** Depth in meters */
	double depth;
	/** Top left corner easting in UTM projection */
	double top_left_corner_e;
	/** Top left corner northing in UTM projection */
	double top_left_corner_n;
	/** Top right corner easting in UTM projection */
	double top_right_corner_e;
	/** Top right corner northing in UTM projection */
	double top_right_corner_n;
	/** Bottom left corner easting in UTM projection */
	double bottom_left_corner_e;
	/** Bottom left corner northing in UTM projection */
	double bottom_left_corner_n;
	/** Bottom right corner easting in UTM projection */
	double bottom_right_corner_e;
	/** Bottom right corner northing in UTM projection */
	double bottom_right_corner_n;
	/** Z interval for the data */
	double depth_interval;
	/** Brocher 2005 scaling polynomial coefficient 10^0 */
	double p0;
	/** Brocher 2005 scaling polynomial coefficient 10^1 */
	double p1;
	/** Brocher 2005 scaling polynomial coefficient 10^2 */
	double p2;
	/** Brocher 2005 scaling polynomial coefficient 10^3 */
	double p3;
	/** Brocher 2005 scaling polynomial coefficient 10^4 */
	double p4;
	/** Brocher 2005 scaling polynomial coefficient 10^5 */
	double p5;
} cvms5_configuration_t;

/** The configuration structure for the Vs30 map. */
typedef struct cvms5_vs30_map_config_t {
	/** Pointer to the e-tree file */
	etree_t *vs30_map;
	/** The type of map */
	char type[20];
	/** A description of the map */
	char description[50];
	/** The map's author */
	char author[30];
	/** The date the map was created */
	char date[10];
	/** The spacing in meters */
	double spacing;
	/** The map's schema */
	char schema[50];
	/** The projection string in Proj.4 format */
	char projection[128];
	/** The origin point */
	cvms5_point_t origin_point;
	/** The number of degrees the map was rotated around origin */
	double rotation;
	/** The X dimension of the map */
	double x_dimension;
	/** The Y dimension of the map */
	double y_dimension;
	/** The Z dimension of the map */
	double z_dimension;
	/** Number of e-tree ticks in the X direction */
	int x_ticks;
	/** Number of e-tree ticks in the Y direction */
	int y_ticks;
	/** Number of e-tree ticks in the Z direction */
	int z_ticks;
} cvms5_vs30_map_config_t;

/** The model structure which points to available portions of the model. */
typedef struct cvms5_model_t {
	/** A pointer to the Vs data either in memory or disk. Null if does not exist. */
	void *vs;
	/** Vs status: 0 = not found, 1 = found and not in memory, 2 = found and in memory */
	int vs_status;
	/** A pointer to the Vp data either in memory or disk. Null if does not exist. */
	void *vp;
	/** Vp status: 0 = not found, 1 = found and not in memory, 2 = found and in memory */
	int vp_status;
	/** A pointer to the rho data either in memory or disk. Null if does not exist. */
	void *rho;
	/** Rho status: 0 = not found, 1 = found and not in memory, 2 = found and in memory */
	int rho_status;
	/** A pointer to the Qp data either in memory or disk. Null if does not exist. */
	void *qp;
	/** Qp status: 0 = not found, 1 = found and not in memory, 2 = found and in memory */
	int qp_status;
	/** A pointer to the Qs data either in memory or disk. Null if does not exist. */
	void *qs;
	/** Qs status: 0 = not found, 1 = found and not in memory, 2 = found and in memory */
	int qs_status;
} cvms5_model_t;

/** Contains the Vs30 and surface values from the UCVM map. */
typedef struct cvms5_vs30_mpayload_t {
	/** Surface height in meters */
	float surf;
	/** Vs30 data from Wills and Wald */
	float vs30;
} cvms5_vs30_mpayload_t;

// Constants
/** The version of the model. */
const char *cvms5_version_string = "CVM-S5";

// Variables
/** Set to 1 when the model is ready for query. */
int cvms5_is_initialized = 0;

/** Location of the ucvm.e e-tree file. */
char vs30_etree_file[128];
/** Location of Po and En-Jui's latest iteration files. */
char cvms5_iteration_directory[128];

/** Configuration parameters. */
cvms5_configuration_t *cvms5_configuration;
/** Holds pointers to the velocity model data OR indicates it can be read from file. */
cvms5_model_t *cvms5_velocity_model;
/** Holds the configuration parameters for the Vs30 map. */
cvms5_vs30_map_config_t *cvms5_vs30_map;

/** Proj.4 latitude longitude, WGS84 projection holder. */
projPJ cvms5_latlon;
/** Proj.4 UTM projection holder. */
projPJ cvms5_utm;
/** Proj.4 Vs30 map projection holder. */
projPJ cvms5_aeqd;

/** The cosine of the rotation angle used to rotate the box and point around the bottom-left corner. */
double cvms5_cos_rotation_angle = 0;
/** The sine of the rotation angle used to rotate the box and point around the bottom-left corner. */
double cvms5_sin_rotation_angle = 0;

/** The height of this model's region, in meters. */
double cvms5_total_height_m = 0;
/** The width of this model's region, in meters. */
double cvms5_total_width_m = 0;

/** The cosine of the Vs30 map's rotation. */
double cvms5_cos_vs30_rotation_angle = 0;
/** The sine of the Vs30 map's rotation. */
double cvms5_sin_vs30_rotation_angle = 0;

// UCVM API Required Functions

#ifdef DYNAMIC_LIBRARY

/** Initializes the model */
int model_init(const char *dir, const char *label);
/** Cleans up the model (frees memory, etc.) */
int model_finalize();
/** Returns version information */
int model_version(char *ver, int len);
/** Queries the model */
int model_query(cvms5_point_t *points, cvms5_properties_t *data, int numpts);


int (*get_model_init())(const char *, const char *);
int (*get_model_query())(cvms5_point_t *, cvms5_properties_t *, int);
int (*get_model_finalize())();
int (*get_model_version())(char *, int);

#endif

// CVM-S5 Related Functions

/** Initializes the model */
int cvms5_init(const char *dir, const char *label);
/** Cleans up the model (frees memory, etc.) */
int cvms5_finalize();
/** Returns version information */
int cvms5_version(char *ver, int len);
/** Queries the model */
int cvms5_query(cvms5_point_t *points, cvms5_properties_t *data, int numpts);

// Non-UCVM Helper Functions
/** Reads the configuration file. */
int cvms5_read_configuration(char *file, cvms5_configuration_t *config);
/** Retrieves the vs30 value for a given point. */
int cvms5_get_vs30_based_gtl(cvms5_point_t *point, cvms5_properties_t *data);
/** Prints out the error string. */
void cvms5_print_error(char *err);
/** Retrieves the value at a specified grid point in the model. */
void cvms5_read_properties(int x, int y, int z, cvms5_properties_t *data);
/** Attempts to malloc the model size in memory and read it in. */
int cvms5_try_reading_model(cvms5_model_t *model);
/** Reads the specified Vs30 map from UCVM. */
int cvms5_read_vs30_map(char *filename, cvms5_vs30_map_config_t *map);
/** Gets the Vs30 value at a point */
double cvms5_get_vs30_value(double longitude, double latitude, cvms5_vs30_map_config_t *map);
/** Calculates density from Vs. */
double cvms5_calculate_density(double vs);

// Interpolation Functions
/** Linearly interpolates two cvms5_properties_t structures */
void cvms5_linear_interpolation(double percent, cvms5_properties_t *x0, cvms5_properties_t *x1, cvms5_properties_t *ret_properties);
/** Bilinearly interpolates the properties. */
void cvms5_bilinear_interpolation(double x_percent, double y_percent, cvms5_properties_t *four_points, cvms5_properties_t *ret_properties);
/** Trilinearly interpolates the properties. */
void cvms5_trilinear_interpolation(double x_percent, double y_percent, double z_percent, cvms5_properties_t *eight_points,
							 cvms5_properties_t *ret_properties);
