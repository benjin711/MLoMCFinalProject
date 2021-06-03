#include "linear_to_mel_weight_list.h"
#include <math.h>


void calc_log_mel_spectrogram(float32_t* magnitude, float32_t* log_mel_spectrogram) {

	// Linear to mel weight matrix condensed as list
	int16_t listsize = 2008;
	float32_t list[] = {
	  5, 9, 0.166302, 10, 0.563328, 11, 0.955716, 12, 0.656423, 13, 0.272992,
	  5, 12, 0.343577, 13, 0.727008, 14, 0.893888, 15, 0.519015, 16, 0.148278,
	  6, 14, 0.106112, 15, 0.480985, 16, 0.851722, 17, 0.781588, 18, 0.418859, 19, 0.060003,
	  6, 17, 0.218412, 18, 0.581141, 19, 0.939997, 20, 0.704941, 21, 0.353587, 22, 0.005875,
	  5, 20, 0.295059, 21, 0.646413, 22, 0.994125, 23, 0.661725, 24, 0.321064,
	  5, 23, 0.338275, 24, 0.678936, 25, 0.983823, 26, 0.649933, 27, 0.319328,
	  7, 25, 0.016177, 26, 0.350067, 27, 0.680672, 28, 0.991947, 29, 0.667726, 30, 0.346603, 31, 0.028520,
	  7, 28, 0.008053, 29, 0.332274, 30, 0.653397, 31, 0.971480, 32, 0.713422, 33, 0.401253, 34, 0.091956,
	  6, 32, 0.286578, 33, 0.598747, 34, 0.908044, 35, 0.785481, 36, 0.481775, 37, 0.180793,
	  7, 35, 0.214519, 36, 0.518225, 37, 0.819207, 38, 0.882485, 39, 0.586798, 40, 0.293693, 41, 0.003121,
	  7, 38, 0.117515, 39, 0.413202, 40, 0.706307, 41, 0.996879, 42, 0.715043, 43, 0.429417, 44, 0.146195,
	  7, 42, 0.284957, 43, 0.570583, 44, 0.853805, 45, 0.865343, 46, 0.586818, 47, 0.310584, 48, 0.036604,
	  7, 45, 0.134657, 46, 0.413182, 47, 0.689416, 48, 0.963396, 49, 0.764840, 50, 0.495253, 51, 0.227817,
	  7, 49, 0.235160, 50, 0.504747, 51, 0.772183, 52, 0.962492, 53, 0.699245, 54, 0.438044, 55, 0.178862,
	  8, 52, 0.037508, 53, 0.300755, 54, 0.561956, 55, 0.821138, 56, 0.921662, 57, 0.666412, 58, 0.413093, 59, 0.161667,
	  8, 56, 0.078338, 57, 0.333588, 58, 0.586908, 59, 0.838333, 60, 0.912110, 61, 0.664392, 62, 0.418489, 63, 0.174372,
	  8, 60, 0.087890, 61, 0.335608, 62, 0.581511, 63, 0.825628, 64, 0.932018, 65, 0.691395, 66, 0.452487, 67, 0.215266,
	  9, 64, 0.067982, 65, 0.308605, 66, 0.547513, 67, 0.784734, 68, 0.979709, 69, 0.745790, 70, 0.513490, 71, 0.282785, 72, 0.053648,
	  9, 68, 0.020291, 69, 0.254210, 70, 0.486510, 71, 0.717215, 72, 0.946352, 73, 0.826069, 74, 0.600021, 75, 0.375484, 76, 0.152443,
	  9, 73, 0.173931, 74, 0.399979, 75, 0.624516, 76, 0.847557, 77, 0.930862, 78, 0.710741, 79, 0.492049, 80, 0.274772, 81, 0.058893,
	  9, 77, 0.069138, 78, 0.289259, 79, 0.507951, 80, 0.725228, 81, 0.941107, 82, 0.844388, 83, 0.631247, 84, 0.419451, 85, 0.208983,
	  9, 82, 0.155612, 83, 0.368753, 84, 0.580549, 85, 0.791017, 86, 0.999824, 87, 0.791955, 88, 0.585370, 89, 0.380046, 90, 0.175967,
	  10, 86, 0.000176, 87, 0.208045, 88, 0.414630, 89, 0.619954, 90, 0.824033, 91, 0.973124, 92, 0.771495, 93, 0.571070, 94, 0.371835, 95, 0.173773,
	  11, 91, 0.026876, 92, 0.228505, 93, 0.428930, 94, 0.628165, 95, 0.826227, 96, 0.976876, 97, 0.781122, 98, 0.586502, 99, 0.393006, 100, 0.200616, 101, 0.009322,
	  11, 96, 0.023124, 97, 0.218878, 98, 0.413497, 99, 0.606994, 100, 0.799384, 101, 0.990678, 102, 0.819111, 103, 0.629972, 104, 0.441889, 105, 0.254855, 106, 0.068854,
	  10, 102, 0.180889, 103, 0.370028, 104, 0.558111, 105, 0.745145, 106, 0.931146, 107, 0.883879, 108, 0.699917, 109, 0.516958, 110, 0.334989, 111, 0.154002,
	  11, 107, 0.116121, 108, 0.300083, 109, 0.483042, 110, 0.665011, 111, 0.845998, 112, 0.973983, 113, 0.794925, 114, 0.616812, 115, 0.439639, 116, 0.263401, 117, 0.088079,
	  12, 112, 0.026017, 113, 0.205075, 114, 0.383188, 115, 0.560361, 116, 0.736599, 117, 0.911921, 118, 0.913671, 119, 0.740158, 120, 0.567540, 121, 0.395807, 122, 0.224943, 123, 0.054945,
	  12, 118, 0.086329, 119, 0.259842, 120, 0.432460, 121, 0.604193, 122, 0.775057, 123, 0.945055, 124, 0.885802, 125, 0.717507, 126, 0.550053, 127, 0.383428, 128, 0.217625, 129, 0.052638,
	  12, 124, 0.114198, 125, 0.282493, 126, 0.449947, 127, 0.616572, 128, 0.782375, 129, 0.947362, 130, 0.888455, 131, 0.725068, 132, 0.562475, 133, 0.400668, 134, 0.239636, 135, 0.079368,
	  12, 130, 0.111545, 131, 0.274932, 132, 0.437525, 133, 0.599332, 134, 0.760364, 135, 0.920632, 136, 0.919864, 137, 0.761114, 138, 0.603105, 139, 0.445843, 140, 0.289312, 141, 0.133505,
	  13, 136, 0.080136, 137, 0.238886, 138, 0.396895, 139, 0.554157, 140, 0.710688, 141, 0.866495, 142, 0.978419, 143, 0.824042, 144, 0.670371, 145, 0.517402, 146, 0.365129, 147, 0.213543, 148, 0.062633,
	  14, 142, 0.021581, 143, 0.175958, 144, 0.329629, 145, 0.482598, 146, 0.634871, 147, 0.786457, 148, 0.937366, 149, 0.912401, 150, 0.762838, 151, 0.613941, 152, 0.465696, 153, 0.318102, 154, 0.171159, 155, 0.024853,
	  14, 149, 0.087599, 150, 0.237162, 151, 0.386059, 152, 0.534304, 153, 0.681898, 154, 0.828841, 155, 0.975147, 156, 0.879180, 157, 0.734136, 158, 0.589718, 159, 0.445916, 160, 0.302724, 161, 0.160144, 162, 0.018168,
	  14, 156, 0.120820, 157, 0.265864, 158, 0.410282, 159, 0.554084, 160, 0.697276, 161, 0.839856, 162, 0.981832, 163, 0.876785, 164, 0.735995, 165, 0.595799, 166, 0.456181, 167, 0.317141, 168, 0.178673, 169, 0.040772,
	  14, 163, 0.123215, 164, 0.264005, 165, 0.404201, 166, 0.543819, 167, 0.682859, 168, 0.821327, 169, 0.959228, 170, 0.903443, 171, 0.766666, 172, 0.630447, 173, 0.494769, 174, 0.359649, 175, 0.225063, 176, 0.091019,
	  15, 170, 0.096557, 171, 0.233334, 172, 0.369553, 173, 0.505231, 174, 0.640351, 175, 0.774937, 176, 0.908981, 177, 0.957503, 178, 0.824519, 179, 0.692059, 180, 0.560119, 181, 0.428692, 182, 0.297782, 183, 0.167377, 184, 0.037475,
	  16, 177, 0.042497, 178, 0.175481, 179, 0.307941, 180, 0.439881, 181, 0.571308, 182, 0.702218, 183, 0.832623, 184, 0.962525, 185, 0.908078, 186, 0.779173, 187, 0.650762, 188, 0.522842, 189, 0.395403, 190, 0.268447, 191, 0.141972, 192, 0.015970,
	  16, 185, 0.091922, 186, 0.220827, 187, 0.349238, 188, 0.477158, 189, 0.604597, 190, 0.731553, 191, 0.858028, 192, 0.984030, 193, 0.890438, 194, 0.765375, 195, 0.640773, 196, 0.516634, 197, 0.392954, 198, 0.269725, 199, 0.146943, 200, 0.024612,
	  16, 193, 0.109562, 194, 0.234625, 195, 0.359227, 196, 0.483366, 197, 0.607046, 198, 0.730275, 199, 0.853057, 200, 0.975388, 201, 0.902726, 202, 0.781272, 203, 0.660266, 204, 0.539693, 205, 0.419546, 206, 0.299828, 207, 0.180539, 208, 0.061669,
	  17, 201, 0.097274, 202, 0.218728, 203, 0.339734, 204, 0.460307, 205, 0.580454, 206, 0.700172, 207, 0.819461, 208, 0.938331, 209, 0.943221, 210, 0.825188, 211, 0.707566, 212, 0.590352, 213, 0.473552, 214, 0.357152, 215, 0.241161, 216, 0.125562, 217, 0.010363,
	  17, 209, 0.056779, 210, 0.174812, 211, 0.292434, 212, 0.409648, 213, 0.526448, 214, 0.642848, 215, 0.758839, 216, 0.874438, 217, 0.989637, 218, 0.895554, 219, 0.781141, 220, 0.667114, 221, 0.553469, 222, 0.440214, 223, 0.327337, 224, 0.214838, 225, 0.102714,
	  18, 218, 0.104446, 219, 0.218859, 220, 0.332886, 221, 0.446531, 222, 0.559786, 223, 0.672663, 224, 0.785162, 225, 0.897286, 226, 0.990961, 227, 0.879580, 228, 0.768562, 229, 0.657919, 230, 0.547633, 231, 0.437714, 232, 0.328144, 233, 0.218939, 234, 0.110083, 235, 0.001583,
	  19, 226, 0.009039, 227, 0.120420, 228, 0.231438, 229, 0.342081, 230, 0.452367, 231, 0.562286, 232, 0.671856, 233, 0.781061, 234, 0.889917, 235, 0.998417, 236, 0.893425, 237, 0.785620, 238, 0.678158, 239, 0.571037, 240, 0.464259, 241, 0.357822, 242, 0.251717, 243, 0.145946, 244, 0.040510,
	  19, 236, 0.106575, 237, 0.214380, 238, 0.321842, 239, 0.428963, 240, 0.535741, 241, 0.642178, 242, 0.748283, 243, 0.854054, 244, 0.959490, 245, 0.935405, 246, 0.830621, 247, 0.726171, 248, 0.622034, 249, 0.518232, 250, 0.414739, 251, 0.311566, 252, 0.208710, 253, 0.106171, 254, 0.003941,
	  19, 245, 0.064595, 246, 0.169379, 247, 0.273829, 248, 0.377966, 249, 0.481768, 250, 0.585261, 251, 0.688434, 252, 0.791290, 253, 0.893829, 254, 0.996059, 255, 0.902023, 256, 0.800412, 257, 0.699102, 258, 0.598102, 259, 0.497404, 260, 0.397011, 261, 0.296910, 262, 0.197114, 263, 0.097609,
	  20, 255, 0.097976, 256, 0.199588, 257, 0.300898, 258, 0.401898, 259, 0.502596, 260, 0.602989, 261, 0.703090, 262, 0.802886, 263, 0.902391, 264, 0.998399, 265, 0.899476, 266, 0.800852, 267, 0.702512, 268, 0.604463, 269, 0.506693, 270, 0.409212, 271, 0.312010, 272, 0.215093, 273, 0.118444, 274, 0.022087,
	  21, 264, 0.001601, 265, 0.100524, 266, 0.199148, 267, 0.297488, 268, 0.395537, 269, 0.493307, 270, 0.590788, 271, 0.687990, 272, 0.784907, 273, 0.881556, 274, 0.977913, 275, 0.925992, 276, 0.830181, 277, 0.734636, 278, 0.639367, 279, 0.544363, 280, 0.449636, 281, 0.355164, 282, 0.260965, 283, 0.167021, 284, 0.073349,
	  21, 275, 0.074008, 276, 0.169819, 277, 0.265364, 278, 0.360633, 279, 0.455637, 280, 0.550363, 281, 0.644836, 282, 0.739035, 283, 0.832979, 284, 0.926651, 285, 0.979929, 286, 0.886766, 287, 0.793869, 288, 0.701224, 289, 0.608836, 290, 0.516696, 291, 0.424818, 292, 0.333181, 293, 0.241801, 294, 0.150662, 295, 0.059773,
	  22, 285, 0.020071, 286, 0.113234, 287, 0.206131, 288, 0.298776, 289, 0.391164, 290, 0.483304, 291, 0.575182, 292, 0.666820, 293, 0.758199, 294, 0.849338, 295, 0.940227, 296, 0.969125, 297, 0.878732, 298, 0.788568, 299, 0.698655, 300, 0.608975, 301, 0.519538, 302, 0.430342, 303, 0.341375, 304, 0.252648, 305, 0.164150, 306, 0.075886,
	  23, 296, 0.030875, 297, 0.121268, 298, 0.211432, 299, 0.301345, 300, 0.391025, 301, 0.480462, 302, 0.569658, 303, 0.658625, 304, 0.747352, 305, 0.835850, 306, 0.924114, 307, 0.987858, 308, 0.900055, 309, 0.812482, 310, 0.725137, 311, 0.638019, 312, 0.551130, 313, 0.464459, 314, 0.378013, 315, 0.291790, 316, 0.205785, 317, 0.120002, 318, 0.034437,
	  24, 307, 0.012142, 308, 0.099945, 309, 0.187518, 310, 0.274863, 311, 0.361981, 312, 0.448870, 313, 0.535541, 314, 0.621987, 315, 0.708210, 316, 0.794215, 317, 0.879998, 318, 0.965563, 319, 0.949087, 320, 0.863955, 321, 0.779038, 322, 0.694339, 323, 0.609851, 324, 0.525571, 325, 0.441509, 326, 0.357647, 327, 0.274004, 328, 0.190560, 329, 0.107332, 330, 0.024299,
	  24, 319, 0.050913, 320, 0.136045, 321, 0.220962, 322, 0.305661, 323, 0.390148, 324, 0.474429, 325, 0.558491, 326, 0.642353, 327, 0.725996, 328, 0.809440, 329, 0.892668, 330, 0.975701, 331, 0.941482, 332, 0.858857, 333, 0.776447, 334, 0.694226, 335, 0.612217, 336, 0.530400, 337, 0.448787, 338, 0.367370, 339, 0.286146, 340, 0.205126, 341, 0.124288, 342, 0.043658,
	  25, 331, 0.058518, 332, 0.141143, 333, 0.223553, 334, 0.305774, 335, 0.387783, 336, 0.469600, 337, 0.551213, 338, 0.632630, 339, 0.713854, 340, 0.794874, 341, 0.875712, 342, 0.956343, 343, 0.963212, 344, 0.882964, 345, 0.802901, 346, 0.723031, 347, 0.643353, 348, 0.563862, 349, 0.484555, 350, 0.405442, 351, 0.326511, 352, 0.247765, 353, 0.169205, 354, 0.090826, 355, 0.012626,
	  26, 343, 0.036788, 344, 0.117036, 345, 0.197099, 346, 0.276969, 347, 0.356647, 348, 0.436138, 349, 0.515445, 350, 0.594558, 351, 0.673489, 352, 0.752235, 353, 0.830795, 354, 0.909174, 355, 0.987374, 356, 0.934619, 357, 0.856783, 358, 0.779129, 359, 0.701657, 360, 0.624355, 361, 0.547240, 362, 0.470299, 363, 0.393529, 364, 0.316941, 365, 0.240520, 366, 0.164274, 367, 0.088210, 368, 0.012306,
	  26, 356, 0.065381, 357, 0.143217, 358, 0.220871, 359, 0.298343, 360, 0.375645, 361, 0.452760, 362, 0.529701, 363, 0.606471, 364, 0.683059, 365, 0.759480, 366, 0.835726, 367, 0.911790, 368, 0.987694, 369, 0.936581, 370, 0.861022, 371, 0.785635, 372, 0.710415, 373, 0.635366, 374, 0.560478, 375, 0.485760, 376, 0.411209, 377, 0.336819, 378, 0.262600, 379, 0.188541, 380, 0.114646, 381, 0.040910,
	  27, 369, 0.063419, 370, 0.138978, 371, 0.214365, 372, 0.289585, 373, 0.364634, 374, 0.439522, 375, 0.514240, 376, 0.588791, 377, 0.663181, 378, 0.737400, 379, 0.811459, 380, 0.885354, 381, 0.959090, 382, 0.967339, 383, 0.893927, 384, 0.820680, 385, 0.747585, 386, 0.674650, 387, 0.601875, 388, 0.529261, 389, 0.456799, 390, 0.384490, 391, 0.312341, 392, 0.240346, 393, 0.168510, 394, 0.096819, 395, 0.025282,
	  28, 382, 0.032661, 383, 0.106073, 384, 0.179320, 385, 0.252415, 386, 0.325350, 387, 0.398125, 388, 0.470739, 389, 0.543201, 390, 0.615510, 391, 0.687658, 392, 0.759654, 393, 0.831490, 394, 0.903181, 395, 0.974718, 396, 0.953897, 397, 0.882666, 398, 0.811587, 399, 0.740654, 400, 0.669874, 401, 0.599239, 402, 0.528757, 403, 0.458413, 404, 0.388222, 405, 0.318184, 406, 0.248284, 407, 0.178530, 408, 0.108921, 409, 0.039458,
	  29, 396, 0.046103, 397, 0.117334, 398, 0.188413, 399, 0.259346, 400, 0.330126, 401, 0.400761, 402, 0.471243, 403, 0.541587, 404, 0.611778, 405, 0.681816, 406, 0.751716, 407, 0.821470, 408, 0.891079, 409, 0.960542, 410, 0.970133, 411, 0.900961, 412, 0.831928, 413, 0.763025, 414, 0.694275, 415, 0.625663, 416, 0.557190, 417, 0.488855, 418, 0.420658, 419, 0.352606, 420, 0.284686, 421, 0.216897, 422, 0.149253, 423, 0.081747, 424, 0.014373,
	  30, 410, 0.029867, 411, 0.099039, 412, 0.168072, 413, 0.236975, 414, 0.305725, 415, 0.374337, 416, 0.442810, 417, 0.511145, 418, 0.579342, 419, 0.647394, 420, 0.715314, 421, 0.783103, 422, 0.850747, 423, 0.918253, 424, 0.985627, 425, 0.947129, 426, 0.880023, 427, 0.813056, 428, 0.746212, 429, 0.679507, 430, 0.612932, 431, 0.546489, 432, 0.480176, 433, 0.414002, 434, 0.347944, 435, 0.282025, 436, 0.216236, 437, 0.150571, 438, 0.085037, 439, 0.019627,
	  30, 425, 0.052871, 426, 0.119977, 427, 0.186944, 428, 0.253788, 429, 0.320493, 430, 0.387068, 431, 0.453511, 432, 0.519824, 433, 0.585998, 434, 0.652056, 435, 0.717975, 436, 0.783764, 437, 0.849429, 438, 0.914963, 439, 0.980373, 440, 0.954349, 441, 0.889201, 442, 0.824170, 443, 0.759270, 444, 0.694493, 445, 0.629840, 446, 0.565311, 447, 0.500906, 448, 0.436624, 449, 0.372467, 450, 0.308432, 451, 0.244522, 452, 0.180728, 453, 0.117050, 454, 0.053504,
	  31, 440, 0.045651, 441, 0.110799, 442, 0.175830, 443, 0.240730, 444, 0.305507, 445, 0.370160, 446, 0.434689, 447, 0.499094, 448, 0.563376, 449, 0.627533, 450, 0.691568, 451, 0.755478, 452, 0.819272, 453, 0.882950, 454, 0.946496, 455, 0.990074, 456, 0.926759, 457, 0.863569, 458, 0.800495, 459, 0.737537, 460, 0.674703, 461, 0.611979, 462, 0.549378, 463, 0.486886, 464, 0.424518, 465, 0.362259, 466, 0.300124, 467, 0.238090, 468, 0.176181, 469, 0.114380, 470, 0.052704,
	  33, 455, 0.009926, 456, 0.073241, 457, 0.136431, 458, 0.199505, 459, 0.262463, 460, 0.325297, 461, 0.388021, 462, 0.450622, 463, 0.513114, 464, 0.575482, 465, 0.637741, 466, 0.699876, 467, 0.761910, 468, 0.823819, 469, 0.885620, 470, 0.947296, 471, 0.991129, 472, 0.929671, 473, 0.868322, 474, 0.807090, 475, 0.745966, 476, 0.684952, 477, 0.624055, 478, 0.563259, 479, 0.502580, 480, 0.442010, 481, 0.381549, 482, 0.321190, 483, 0.260947, 484, 0.200806, 485, 0.140775, 486, 0.080860, 487, 0.021039,
	  34, 471, 0.008871, 472, 0.070329, 473, 0.131678, 474, 0.192910, 475, 0.254034, 476, 0.315048, 477, 0.375945, 478, 0.436741, 479, 0.497420, 480, 0.557990, 481, 0.618451, 482, 0.678810, 483, 0.739053, 484, 0.799194, 485, 0.859225, 486, 0.919140, 487, 0.978961, 488, 0.961328, 489, 0.901725, 490, 0.842225, 491, 0.782834, 492, 0.723537, 493, 0.664357, 494, 0.605279, 495, 0.546295, 496, 0.487428, 497, 0.428656, 498, 0.369985, 499, 0.311423, 500, 0.252956, 501, 0.194591, 502, 0.136336, 503, 0.078167, 504, 0.020115
	};

	float32_t sum = 0;
	int num_elements = 0;
	int bin_counter = 0;
	for(int outer = 0; outer < listsize; ){
		sum = 0;
		num_elements = 2 * list[outer];

		for(int inner = 1; inner < num_elements; inner = inner + 2){
			sum += magnitude[(int)list[outer + inner]] * list[outer + inner + 1];
		}

		log_mel_spectrogram[bin_counter] = log(sum + 1e-6);
		outer += 1 + num_elements;
		bin_counter++;

	}

}

