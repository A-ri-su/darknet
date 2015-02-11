#ifndef CONVOLUTIONAL_LAYER_H
#define CONVOLUTIONAL_LAYER_H

#include "cuda.h"
#include "image.h"
#include "activations.h"

typedef struct {
    float learning_rate;
    float momentum;
    float decay;

    int batch;
    int h,w,c;
    int n;
    int size;
    int stride;
    int pad;
    float *filters;
    float *filter_updates;

    float *biases;
    float *bias_updates;

    float *col_image;
    float *delta;
    float *output;

    #ifdef GPU
    float * filters_gpu;
    float * filter_updates_gpu;

    float * biases_gpu;
    float * bias_updates_gpu;

    float * col_image_gpu;
    float * delta_gpu;
    float * output_gpu;
    #endif

    ACTIVATION activation;
} convolutional_layer;

#ifdef GPU
void forward_convolutional_layer_gpu(convolutional_layer layer, float * in);
void backward_convolutional_layer_gpu(convolutional_layer layer, float * in, float * delta_gpu);
void update_convolutional_layer_gpu(convolutional_layer layer);

void push_convolutional_layer(convolutional_layer layer);
void pull_convolutional_layer(convolutional_layer layer);

void bias_output_gpu(float *output, float *biases, int batch, int n, int size);
void backward_bias_gpu(float *bias_updates, float *delta, int batch, int n, int size);
#endif

convolutional_layer *make_convolutional_layer(int batch, int h, int w, int c, int n, int size, int stride, int pad, ACTIVATION activation, float learning_rate, float momentum, float decay);
void resize_convolutional_layer(convolutional_layer *layer, int h, int w);
void forward_convolutional_layer(const convolutional_layer layer, float *in);
void update_convolutional_layer(convolutional_layer layer);
image *visualize_convolutional_layer(convolutional_layer layer, char *window, image *prev_filters);

void backward_convolutional_layer(convolutional_layer layer, float *in, float *delta);

void bias_output(float *output, float *biases, int batch, int n, int size);
void backward_bias(float *bias_updates, float *delta, int batch, int n, int size);

image get_convolutional_image(convolutional_layer layer);
image get_convolutional_delta(convolutional_layer layer);
image get_convolutional_filter(convolutional_layer layer, int i);

int convolutional_out_height(convolutional_layer layer);
int convolutional_out_width(convolutional_layer layer);

#endif

