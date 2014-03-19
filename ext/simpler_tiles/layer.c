#include "layer.h"
#include <simple-tiles/layer.h>
#include <simple-tiles/query.h>
#include <simple-tiles/list.h>

VALUE cSimplerTilesLayer;

static simplet_layer_t *
get_layer(VALUE self){
  simplet_layer_t *layer;
  Data_Get_Struct(self, simplet_layer_t, layer);
  return layer;
}

static void
mark_layer(void *layer){
  simplet_layer_t *lyr = layer;
  VALUE ref = (VALUE)simplet_layer_get_user_data(lyr);
  if(ref) rb_gc_mark(ref);
}

static void
layer_free(void *layer){
  simplet_layer_t *lyr = layer;
  simplet_layer_free(lyr);
}


/*
Set the source attribute for the Layer.

@return (String)
@param (String)
*/
static VALUE
set_source(VALUE self, VALUE source){
  Check_Type(source, T_STRING);
  simplet_layer_t *layer = get_layer(self);
  simplet_layer_set_source(layer, RSTRING_PTR(source));
  return source;
}

/*
Get a copy of the Layer's source.

@return (String)
*/
static VALUE
get_source(VALUE self) {
  simplet_layer_t *layer = get_layer(self);
  char *source;
  simplet_layer_get_source(layer, &source);
  return rb_str_new2(source);
}

/*
Add a query object to this Layer's list of queries.

@param (String)
@return (Query)
*/
static VALUE
add_query(VALUE self, VALUE query){
  simplet_layer_t *layer = get_layer(self);
  simplet_query_t *qry;
  Data_Get_Struct(query, simplet_query_t, qry);
  simplet_layer_add_query_directly(layer, qry);
  VALUE circ_ref = self;
  simplet_query_set_user_data(qry, (void *)circ_ref);
  simplet_retain((simplet_retainable_t*) qry);
  return query;
}

VALUE
layer_alloc(VALUE klass){
  simplet_layer_t *layer;
  if(!(layer = simplet_layer_new("")))
    rb_fatal("Could not allocate space for a new SimplerTiles::Layer in memory.");

  return Data_Wrap_Struct(klass, mark_layer, layer_free, layer);
}

void init_layer(){
  VALUE rlayer = rb_define_class_under(mSimplerTiles, "Layer", rb_cObject);
  rb_define_alloc_func(rlayer, layer_alloc);
  rb_define_method(rlayer, "source=", set_source, 1);
  rb_define_method(rlayer, "source", get_source, 0);
  rb_define_private_method(rlayer, "add_query", add_query, 1);

  cSimplerTilesLayer = rlayer;
}
