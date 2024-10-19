/* -- THIS FILE IS GENERATED - DO NOT EDIT *//* -*- Mode: C; c-basic-offset: 4 -*- */

#define PY_SSIZE_T_CLEAN
#include <Python.h>




#if PY_VERSION_HEX < 0x02050000
typedef int Py_ssize_t;
#define PY_SSIZE_T_MAX INT_MAX
#define PY_SSIZE_T_MIN INT_MIN
typedef inquiry lenfunc;
typedef intargfunc ssizeargfunc;
typedef intobjargproc ssizeobjargproc;
#endif


#line 24 "/home/thread/dev/meld/git/threader/meld-1.8/deps/pygtk-2.24/pygtk-2.24.0/gtk/libglade.override"
#define NO_IMPORT_PYGOBJECT
#include <pygobject.h>
#include <glade/glade.h>
#ifdef HAVE_CONFIG_H
#include "config.h"
#endif
#include <libintl.h>

#include <glib-object.h>

typedef struct {
    GladeXML parent;
    PyObject *typedict;
} PyGladeXML;

typedef struct {
    GladeXMLClass parent_class;
} PyGladeXMLClass;

static void  pyglade_xml_init (PyGladeXML *self);
static void  pyglade_xml_class_init (PyGladeXMLClass *class);
static GType        pyglade_xml_get_type            (void);
static GType pyglade_xml_lookup_type (GladeXML*self, const char *gtypename);

#define PYGLADE_TYPE_XML            (pyglade_xml_get_type())
#define PYGLADE_XML(obj)            (G_TYPE_CHECK_INSTANCE_CAST ((obj), PYGLADE_TYPE_XML, PyGladeXML))
#define PYGLADE_XML_CLASS(klass)    (G_TYPE_CHECK_CLASS_CAST ((klass), PYGLADE_TYPE_XML, PyGladeXMLClass))
#define PYGLADE_IS_XML(obj)         (G_TYPE_CHECK_INSTANCE_TYPE ((obj), PYGLADE_TYPE_XML))
#define PYGLADE_IS_XML_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((obj), PYGLADE_TYPE_XML))
#define PYGLADE_XML_GET_CLASS(obj)  (G_TYPE_INSTANCE_GET_CLASS((obj), PYGLADE_TYPE_XML, PygladeXMLClass))

static GType
pyglade_xml_get_type (void)
{
    static GType xml_type = 0;

    if (!xml_type) {
	static const GTypeInfo xml_info = {
	    sizeof(PyGladeXMLClass),
	    (GBaseInitFunc) NULL,
	    (GBaseFinalizeFunc) NULL,
	    (GClassInitFunc) pyglade_xml_class_init,
	    (GClassFinalizeFunc) NULL,
	    NULL,

	    sizeof (PyGladeXML),
	    0, /* n_preallocs */
	    (GInstanceInitFunc) pyglade_xml_init,
	};

	xml_type = g_type_register_static(GLADE_TYPE_XML, "PyGladeXML",
					  &xml_info, 0);
    }
    return xml_type;

}

static void
pyglade_xml_init (PyGladeXML *self)
{
    self->typedict = PyDict_New();
}

static void
pyglade_xml_class_init (PyGladeXMLClass *class)
{
    GladeXMLClass *xml_class = (GladeXMLClass*)class;
    xml_class->lookup_type = pyglade_xml_lookup_type;
}

static GType
pyglade_xml_lookup_type(GladeXML *glade, const char *gtypename)
{
    PyGladeXML *self;
    PyObject *item;

    g_return_val_if_fail (PYGLADE_IS_XML (glade), G_TYPE_INVALID);

    self = PYGLADE_XML(glade);
    if (self->typedict) {
        item = PyMapping_GetItemString(self->typedict, (char *) gtypename);
	if (!item) {
	    PyErr_Clear();
	    item = NULL;
	}
    } else
        item = NULL;

    if (item != NULL) {
	GType type;

	if ((type = pyg_type_from_object(item)) == 0)
            type = G_TYPE_INVALID;

        Py_DECREF(item);
	return type;
    }
    
    return g_type_from_name(gtypename);
}

static PyGladeXML *
pyglade_xml_new (char * fname, char * root, char *domain, PyObject *dict)
{
    PyGladeXML *self = g_object_new(PYGLADE_TYPE_XML, NULL);

    /* This must be done before, since it's used inside of
     * glade_xml_construct
     */
    self->typedict = dict;
    if (!glade_xml_construct(GLADE_XML(self), fname, root, domain)) {
	g_object_unref(self);
	return NULL;
    }
      /* the reference is borrowed, and we don't need anymore */
    self->typedict = NULL;
    
    return self;
}

#line 141 "/home/thread/dev/meld/git/threader/meld-1.8/deps/pygtk-2.24/pygtk-2.24.0/gtk/libglade.c"


/* ---------- types from other modules ---------- */
static PyTypeObject *_PyGObject_Type;
#define PyGObject_Type (*_PyGObject_Type)
static PyTypeObject *_PyGtkWidget_Type;
#define PyGtkWidget_Type (*_PyGtkWidget_Type)


/* ---------- forward type declarations ---------- */
PyTypeObject G_GNUC_INTERNAL PyGladeXML_Type;

#line 154 "/home/thread/dev/meld/git/threader/meld-1.8/deps/pygtk-2.24/pygtk-2.24.0/gtk/libglade.c"



/* ----------- GladeXML ----------- */

#line 522 "/home/thread/dev/meld/git/threader/meld-1.8/deps/pygtk-2.24/pygtk-2.24.0/gtk/libglade.override"
static int
_wrap_glade_xml_new(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "fname", "root", "domain", "typedict", NULL };
    char *fname, *root = NULL, *domain = NULL;
    PyObject *pydict = NULL;
	
    if (!PyArg_ParseTupleAndKeywords(args, kwargs,
				     "s|zzO:GladeXML.__init__",
				     kwlist, &fname, &root, &domain,
				     &pydict))
        return -1;

    if (pydict && !PyMapping_Check(pydict)) {
        PyErr_SetString(PyExc_TypeError,
			"typedict must be a mapping");
	return -1;
    }

    self->obj = (GObject *) pyglade_xml_new(fname, root, domain, pydict);

    if (!self->obj) {
        PyErr_SetString(PyExc_RuntimeError, "could not create GladeXML object");
        return -1;
    }
    pygobject_register_wrapper((PyObject *)self);
    return 0;
}
#line 189 "/home/thread/dev/meld/git/threader/meld-1.8/deps/pygtk-2.24/pygtk-2.24.0/gtk/libglade.c"


#line 162 "/home/thread/dev/meld/git/threader/meld-1.8/deps/pygtk-2.24/pygtk-2.24.0/gtk/libglade.override"
static void
connect_one(const gchar *handler_name, GObject *obj,
            const gchar *signal_name, const gchar *signal_data,
            GObject *connect_object, gboolean after, gpointer user_data)
{
    GClosure *closure = NULL;
    PyObject *callback = PyTuple_GetItem((PyObject *)user_data, 0);
    PyObject *extra = PyTuple_GetItem((PyObject *)user_data, 1);
    PyObject *self;

    if (connect_object) {
        PyObject *other;

        other = pygobject_new(connect_object);
	closure = pyg_closure_new(callback, extra, other);
    } else {
	closure = pyg_closure_new(callback, extra, NULL);
    }

    self = pygobject_new(obj);
    g_signal_connect_closure(obj, signal_name, closure, after);
    pygobject_watch_closure(self, closure);
    Py_DECREF(self);
}

static PyObject *
_wrap_glade_xml_signal_connect(PyGObject *self, PyObject *args)
{
    guint len;
    PyObject *first, *callback, *extra_args = NULL, *data;
    gchar *handler_name;

    len = PyTuple_Size(args);
    if (len < 2) {
	PyErr_SetString(PyExc_TypeError,
		"GladeXML.signal_connect requires at least 2 arguments");
	return NULL;
    }
    first = PySequence_GetSlice(args, 0, 2);
    if (!PyArg_ParseTuple(first, "sO:GladeXML.signal_connect", &handler_name,
			  &callback)) {
	Py_DECREF(first);
	return NULL;
    }
    Py_DECREF(first);
    if (!PyCallable_Check(callback)) {
	PyErr_SetString(PyExc_TypeError, "second argument must be callable");
	return NULL;
    }
    extra_args = PySequence_GetSlice(args, 2, len);
    if (extra_args == NULL)
	return NULL;
    data = Py_BuildValue("(ON)", callback, extra_args);
    glade_xml_signal_connect_full(GLADE_XML(self->obj), handler_name,
				  connect_one, data);
    Py_DECREF(data);
    Py_INCREF(Py_None);
    return Py_None;
}
#line 252 "/home/thread/dev/meld/git/threader/meld-1.8/deps/pygtk-2.24/pygtk-2.24.0/gtk/libglade.c"


#line 223 "/home/thread/dev/meld/git/threader/meld-1.8/deps/pygtk-2.24/pygtk-2.24.0/gtk/libglade.override"
static void
connect_many(const gchar *handler_name, GObject *obj,
	     const gchar *signal_name, const gchar *signal_data,
	     GObject *connect_object, gboolean after, gpointer user_data)
{
    PyObject *handler_dict = user_data;
    PyObject *tuple, *self;
    GClosure *closure = NULL;

    tuple = PyMapping_GetItemString(handler_dict, (gchar *)handler_name);
    if (!tuple) {
	PyErr_Clear();	
        tuple = PyObject_GetAttrString(handler_dict, (gchar *)handler_name);
        if (!tuple) {
            PyErr_Clear();
            return;
        }
    }
    
    if (PyTuple_Check(tuple)) {
	PyObject *callback = PyTuple_GetItem(tuple, 0);
	PyObject *extra = PySequence_GetSlice(tuple, 1, PyTuple_Size(tuple));
	PyObject *other = NULL;

	if (connect_object)
	    other = pygobject_new((GObject *)connect_object);

	closure = pyg_closure_new(callback, extra, other);
	Py_DECREF(extra);
    } else if (PyCallable_Check(tuple)) {
	PyObject *other = NULL;

	if (connect_object)
	    other = pygobject_new((GObject *)connect_object);

	closure = pyg_closure_new(tuple, NULL, other);
    } else {
	g_warning("handler for `%s' not callable or a tuple", handler_name);
	Py_DECREF(tuple);
	return;
    }
    Py_DECREF(tuple);
    self = pygobject_new(obj);
    g_signal_connect_closure(obj, signal_name, closure, after);
    pygobject_watch_closure(self, closure);
    Py_DECREF(self);
}

static PyObject *
_wrap_glade_xml_signal_autoconnect(PyGObject *self, PyObject *args,
				   PyObject *kwargs)
{
    static char *kwlist[] = { "dict", NULL };
    PyObject *object;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs,
				     "O:GladeXML.signal_autoconnect", kwlist,
				     &object))
	return NULL;

    glade_xml_signal_autoconnect_full(GLADE_XML(self->obj),
				      connect_many,
				      object);
    Py_INCREF(Py_None);
    return Py_None;
}
#line 322 "/home/thread/dev/meld/git/threader/meld-1.8/deps/pygtk-2.24/pygtk-2.24.0/gtk/libglade.c"


static PyObject *
_wrap_glade_xml_get_widget(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "name", NULL };
    char *name;
    GtkWidget *ret;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs,"s:Glade.XML.get_widget", kwlist, &name))
        return NULL;
    
    ret = glade_xml_get_widget(GLADE_XML(self->obj), name);
    
    /* pygobject_new handles NULL checking */
    return pygobject_new((GObject *)ret);
}

#line 291 "/home/thread/dev/meld/git/threader/meld-1.8/deps/pygtk-2.24/pygtk-2.24.0/gtk/libglade.override"
static PyObject *
_wrap_glade_xml_get_widget_prefix(PyGObject *self, PyObject *args,
				  PyObject *kwargs)
{
    static char *kwlist[] = { "name", NULL };
    char *name;
    GList *ret, *tmp;
    PyObject *py_ret;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs,
				     "s:GladeXML.get_widget_prefix", kwlist,
				     &name))
	return NULL;
    ret = glade_xml_get_widget_prefix(GLADE_XML(self->obj), name);
    py_ret = PyList_New(0);
    for (tmp = ret; tmp != NULL; tmp = tmp->next) {
	GtkWidget *widget = tmp->data;
	PyObject *py_widget = pygobject_new((GObject *)widget);

	if (!py_widget) {
	    g_list_free(ret);
	    Py_DECREF(py_ret);
	    return NULL;
	}
	PyList_Append(py_ret, py_widget);
	Py_DECREF(py_widget);
    }
    g_list_free(ret);
    return py_ret;
}
#line 372 "/home/thread/dev/meld/git/threader/meld-1.8/deps/pygtk-2.24/pygtk-2.24.0/gtk/libglade.c"


static PyObject *
_wrap_glade_xml_relative_file(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "filename", NULL };
    char *filename;
    gchar *ret;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs,"s:Glade.XML.relative_file", kwlist, &filename))
        return NULL;
    
    ret = glade_xml_relative_file(GLADE_XML(self->obj), filename);
    
    if (ret) {
        PyObject *py_ret = PyString_FromString(ret);
        g_free(ret);
        return py_ret;
    }
    Py_INCREF(Py_None);
    return Py_None;
}

static const PyMethodDef _PyGladeXML_methods[] = {
    { "signal_connect", (PyCFunction)_wrap_glade_xml_signal_connect, METH_VARARGS,
      NULL },
    { "signal_autoconnect", (PyCFunction)_wrap_glade_xml_signal_autoconnect, METH_VARARGS|METH_KEYWORDS,
      NULL },
    { "get_widget", (PyCFunction)_wrap_glade_xml_get_widget, METH_VARARGS|METH_KEYWORDS,
      NULL },
    { "get_widget_prefix", (PyCFunction)_wrap_glade_xml_get_widget_prefix, METH_VARARGS|METH_KEYWORDS,
      NULL },
    { "relative_file", (PyCFunction)_wrap_glade_xml_relative_file, METH_VARARGS|METH_KEYWORDS,
      NULL },
    { NULL, NULL, 0, NULL }
};

PyTypeObject G_GNUC_INTERNAL PyGladeXML_Type = {
    PyObject_HEAD_INIT(NULL)
    0,                                 /* ob_size */
    "gtk.glade.XML",                   /* tp_name */
    sizeof(PyGObject),          /* tp_basicsize */
    0,                                 /* tp_itemsize */
    /* methods */
    (destructor)0,        /* tp_dealloc */
    (printfunc)0,                      /* tp_print */
    (getattrfunc)0,       /* tp_getattr */
    (setattrfunc)0,       /* tp_setattr */
    (cmpfunc)0,           /* tp_compare */
    (reprfunc)0,             /* tp_repr */
    (PyNumberMethods*)0,     /* tp_as_number */
    (PySequenceMethods*)0, /* tp_as_sequence */
    (PyMappingMethods*)0,   /* tp_as_mapping */
    (hashfunc)0,             /* tp_hash */
    (ternaryfunc)0,          /* tp_call */
    (reprfunc)0,              /* tp_str */
    (getattrofunc)0,     /* tp_getattro */
    (setattrofunc)0,     /* tp_setattro */
    (PyBufferProcs*)0,  /* tp_as_buffer */
    Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE,                      /* tp_flags */
    NULL,                        /* Documentation string */
    (traverseproc)0,     /* tp_traverse */
    (inquiry)0,             /* tp_clear */
    (richcmpfunc)0,   /* tp_richcompare */
    offsetof(PyGObject, weakreflist),             /* tp_weaklistoffset */
    (getiterfunc)0,          /* tp_iter */
    (iternextfunc)0,     /* tp_iternext */
    (struct PyMethodDef*)_PyGladeXML_methods, /* tp_methods */
    (struct PyMemberDef*)0,              /* tp_members */
    (struct PyGetSetDef*)0,  /* tp_getset */
    NULL,                              /* tp_base */
    NULL,                              /* tp_dict */
    (descrgetfunc)0,    /* tp_descr_get */
    (descrsetfunc)0,    /* tp_descr_set */
    offsetof(PyGObject, inst_dict),                 /* tp_dictoffset */
    (initproc)_wrap_glade_xml_new,             /* tp_init */
    (allocfunc)0,           /* tp_alloc */
    (newfunc)0,               /* tp_new */
    (freefunc)0,             /* tp_free */
    (inquiry)0              /* tp_is_gc */
};



/* ----------- functions ----------- */

static PyObject *
_wrap_glade_xml_new_from_buffer(PyObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "buffer", "size", "root", "domain", NULL };
    char *buffer, *root = NULL, *domain = NULL;
    int size;
    GladeXML *ret;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs,"si|zz:xml_new_from_buffer", kwlist, &buffer, &size, &root, &domain))
        return NULL;
    
    ret = glade_xml_new_from_buffer(buffer, size, root, domain);
    
    /* pygobject_new handles NULL checking */
    return pygobject_new((GObject *)ret);
}

static PyObject *
_wrap_glade_get_widget_name(PyObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "widget", NULL };
    PyGObject *widget;
    const gchar *ret;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs,"O!:get_widget_name", kwlist, &PyGtkWidget_Type, &widget))
        return NULL;
    
    ret = glade_get_widget_name(GTK_WIDGET(widget->obj));
    
    if (ret)
        return PyString_FromString(ret);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_glade_get_widget_tree(PyObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "widget", NULL };
    PyGObject *widget;
    GladeXML *ret;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs,"O!:get_widget_tree", kwlist, &PyGtkWidget_Type, &widget))
        return NULL;
    
    ret = glade_get_widget_tree(GTK_WIDGET(widget->obj));
    
    /* pygobject_new handles NULL checking */
    return pygobject_new((GObject *)ret);
}

#line 364 "/home/thread/dev/meld/git/threader/meld-1.8/deps/pygtk-2.24/pygtk-2.24.0/gtk/libglade.override"

/* stores the handler set by set_custom_handler */
static PyObject *pyglade_handler = NULL;
static PyObject *pyglade_user_data = NULL;

static GtkWidget *
pyglade_custom_widget_handler(GladeXML *xml,
			      gchar *func_name,
			      gchar *name,
			      gchar *string1,
			      gchar *string2,
			      gint int1,
			      gint int2,
			      gpointer user_data)
{
    PyObject *firstargs, *args;
    PyObject *widget;
    GtkWidget *ret;

    g_return_val_if_fail(pyglade_handler != NULL, NULL);
    g_return_val_if_fail(pyglade_user_data != NULL, NULL);

    firstargs = Py_BuildValue("Nssssii", pygobject_new((GObject *)xml),
			      func_name, name, string1, string2,
			      int1, int2);
    args = PySequence_Concat(firstargs, pyglade_user_data);
    Py_DECREF(firstargs);

    widget = PyObject_CallObject(pyglade_handler, args);
    Py_DECREF(args);
    if (!widget) {
	PyErr_Print();
	ret = NULL;
    } else if (pygobject_check(widget, &PyGtkWidget_Type)) {
	/* this leaks a reference :( */
	ret = GTK_WIDGET(pygobject_get(widget));
    } else {
	Py_DECREF(widget);
	g_warning("return value of custom widget handler was not a GtkWidget");
	ret = NULL;
    }
    
    return ret;
}

static PyObject *
_wrap_glade_set_custom_handler(PyObject *self, PyObject *args)
{
    PyObject *first, *handler, *user_data;
    gint len;

    len = PyTuple_Size(args);
    if (len < 1) {
	PyErr_SetString(PyExc_TypeError, "set_custom_handler requires at least 1 argument");
	return NULL;
    }
    first = PySequence_GetSlice(args, 0, 1);
    if (!PyArg_ParseTuple(first, "O:set_custom_handler", &handler)) {
	Py_DECREF(first);
	return NULL;
    }
    Py_DECREF(first);
    if (!PyCallable_Check(handler)) {
	PyErr_SetString(PyExc_TypeError, "handler must be callable");
	return NULL;
    }
    user_data = PySequence_GetSlice(args, 1, len);

    /* clear saved data */
    Py_XDECREF(pyglade_handler);
    pyglade_handler = NULL;
    Py_XDECREF(pyglade_user_data);
    pyglade_user_data = NULL;

    /* store new handlers */
    Py_INCREF(handler);
    pyglade_handler = handler;
    pyglade_user_data = user_data;

    /* set handler */
    glade_set_custom_handler(pyglade_custom_widget_handler, NULL);

    Py_INCREF(Py_None);
    return Py_None;
}
#line 596 "/home/thread/dev/meld/git/threader/meld-1.8/deps/pygtk-2.24/pygtk-2.24.0/gtk/libglade.c"


#line 323 "/home/thread/dev/meld/git/threader/meld-1.8/deps/pygtk-2.24/pygtk-2.24.0/gtk/libglade.override"
static PyObject *
_wrap_glade_bindtextdomain(PyObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "domainname", "dirname", NULL };
    char *domainname, *dirname = NULL, *ret;
    
    if (!PyArg_ParseTupleAndKeywords(args, kwargs,
				     "s|s:glade.bindtextdomain", kwlist,
				     &domainname, &dirname))
	return NULL;
    ret = bindtextdomain(domainname, dirname);
    if (!ret) {
	PyErr_SetString(PyExc_MemoryError, "Not enough memory available.");
	return NULL;
    }
#ifdef HAVE_BIND_TEXTDOMAIN_CODESET
    bind_textdomain_codeset(domainname, "UTF-8");
#endif
    return PyString_FromString(ret);
}
#line 620 "/home/thread/dev/meld/git/threader/meld-1.8/deps/pygtk-2.24/pygtk-2.24.0/gtk/libglade.c"


#line 345 "/home/thread/dev/meld/git/threader/meld-1.8/deps/pygtk-2.24/pygtk-2.24.0/gtk/libglade.override"
static PyObject *
_wrap_glade_textdomain(PyObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "domainname", NULL };
    char *domainname = NULL, *ret;
    
    if (!PyArg_ParseTupleAndKeywords(args, kwargs,
				     "|s:glade.textdomain", kwlist,
				     &domainname))
	return NULL;
    ret = textdomain(domainname);
    if (!ret) {
	PyErr_SetString(PyExc_MemoryError, "Not enough memory available.");
	return NULL;
    }
    return PyString_FromString(ret);
}
#line 641 "/home/thread/dev/meld/git/threader/meld-1.8/deps/pygtk-2.24/pygtk-2.24.0/gtk/libglade.c"


#line 451 "/home/thread/dev/meld/git/threader/meld-1.8/deps/pygtk-2.24/pygtk-2.24.0/gtk/libglade.override"
static GtkWidget *
pyglade_custom_widget_callbacks_handler(GladeXML *xml,
					gchar *func_name,
					gchar *name,
					gchar *string1,
					gchar *string2,
					gint int1,
					gint int2,
					gpointer user_data)
{
    PyObject *handler, *widget;
    GtkWidget *ret;

    handler = PyMapping_GetItemString(pyglade_user_data, func_name);
    if (!handler) {
        PyErr_Clear();
        handler = PyObject_GetAttrString(pyglade_user_data, func_name);
        if (!handler) {
            PyErr_Clear();
	    g_warning("could not find handler %s", func_name);
            return NULL;
        }
    }
    if (!PyCallable_Check(handler)) {
	g_warning("object is not callable");
	return NULL;
    }
    
    widget = PyObject_CallFunction(handler, NULL);
    if (pygobject_check(widget, &PyGtkWidget_Type)) {
	/* this leaks a reference :( */
	ret = GTK_WIDGET(pygobject_get(widget));
    } else {
	Py_DECREF(widget);
	g_warning("return value of custom widget handler was not a GtkWidget");
	ret = NULL;
    }
    return ret;
}
static PyObject *
_wrap_glade_set_custom_widget_callbacks(PyObject *self, PyObject *args,
					PyObject *kwargs)
{
    static char *kwlist[] = { "dict", NULL };
    PyObject *object;

    if (PyErr_Warn(PyExc_DeprecationWarning, "use set_custom_handler instead") < 0)
	return NULL;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs,
				     "O:GladeXML.set_custom_widget_callbacks",
				     kwlist, &object))
	return NULL;

    /* clear saved data */
    Py_XDECREF(pyglade_handler);
    pyglade_handler = NULL;
    Py_XDECREF(pyglade_user_data);
    pyglade_user_data = NULL;

    /* store new handlers */
    Py_INCREF(object);
    pyglade_user_data = object;

    glade_set_custom_handler(pyglade_custom_widget_callbacks_handler, NULL);

    Py_INCREF(Py_None);
    return Py_None;
}
#line 714 "/home/thread/dev/meld/git/threader/meld-1.8/deps/pygtk-2.24/pygtk-2.24.0/gtk/libglade.c"


const PyMethodDef pylibglade_functions[] = {
    { "xml_new_from_buffer", (PyCFunction)_wrap_glade_xml_new_from_buffer, METH_VARARGS|METH_KEYWORDS,
      NULL },
    { "get_widget_name", (PyCFunction)_wrap_glade_get_widget_name, METH_VARARGS|METH_KEYWORDS,
      NULL },
    { "get_widget_tree", (PyCFunction)_wrap_glade_get_widget_tree, METH_VARARGS|METH_KEYWORDS,
      NULL },
    { "set_custom_handler", (PyCFunction)_wrap_glade_set_custom_handler, METH_VARARGS,
      NULL },
    { "bindtextdomain", (PyCFunction)_wrap_glade_bindtextdomain, METH_VARARGS|METH_KEYWORDS,
      NULL },
    { "textdomain", (PyCFunction)_wrap_glade_textdomain, METH_VARARGS|METH_KEYWORDS,
      NULL },
    { "set_custom_widget_callbacks", (PyCFunction)_wrap_glade_set_custom_widget_callbacks, METH_VARARGS|METH_KEYWORDS,
      NULL },
    { NULL, NULL, 0, NULL }
};

/* initialise stuff extension classes */
void
pylibglade_register_classes(PyObject *d)
{
    PyObject *module;

    if ((module = PyImport_ImportModule("gobject")) != NULL) {
        _PyGObject_Type = (PyTypeObject *)PyObject_GetAttrString(module, "GObject");
        if (_PyGObject_Type == NULL) {
            PyErr_SetString(PyExc_ImportError,
                "cannot import name GObject from gobject");
            return ;
        }
    } else {
        PyErr_SetString(PyExc_ImportError,
            "could not import gobject");
        return ;
    }
    if ((module = PyImport_ImportModule("gtk")) != NULL) {
        _PyGtkWidget_Type = (PyTypeObject *)PyObject_GetAttrString(module, "Widget");
        if (_PyGtkWidget_Type == NULL) {
            PyErr_SetString(PyExc_ImportError,
                "cannot import name Widget from gtk");
            return ;
        }
    } else {
        PyErr_SetString(PyExc_ImportError,
            "could not import gtk");
        return ;
    }


#line 767 "/home/thread/dev/meld/git/threader/meld-1.8/deps/pygtk-2.24/pygtk-2.24.0/gtk/libglade.c"
    pygobject_register_class(d, "GladeXML", GLADE_TYPE_XML, &PyGladeXML_Type, Py_BuildValue("(O)", &PyGObject_Type));
}
