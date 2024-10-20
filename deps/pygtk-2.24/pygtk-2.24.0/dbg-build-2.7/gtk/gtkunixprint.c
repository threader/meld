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


#line 24 "/home/thread/dev/meld/git/threader/meld-1.8/deps/pygtk-2.24/pygtk-2.24.0/gtk/gtkunixprint.override"
#define NO_IMPORT_PYGOBJECT
#include <pygobject.h>
#ifdef HAVE_CONFIG_H
#include "config.h"
#endif
#include <libintl.h>

#include <glib-object.h>
#include "pygtk-private.h"
#include <gtk/gtk.h>
#include <gtk/gtkunixprint.h>

#include <pycairo.h>
extern Pycairo_CAPI_t *Pycairo_CAPI;

#ifndef GTK_TYPE_PRINT_CAPABILITIES
GType gtk_print_capabilites_get_type (void) G_GNUC_CONST;
#define GTK_TYPE_PRINT_CAPABILITIES (gtk_print_capabilites_get_type())

GType
gtk_print_capabilites_get_type (void)
{
  static GType etype = 0;
  if (etype == 0) {
    static const GFlagsValue values[] = {
      { GTK_PRINT_CAPABILITY_PAGE_SET, "GTK_PRINT_CAPABILITY_PAGE_SET", "page_set" },
      { GTK_PRINT_CAPABILITY_COPIES, "GTK_PRINT_CAPABILITY_COPIES", "copies" },
      { GTK_PRINT_CAPABILITY_COLLATE, "GTK_PRINT_CAPABILITY_COLLATE", "collate" },
      { GTK_PRINT_CAPABILITY_REVERSE, "GTK_PRINT_CAPABILITY_REVERSE", "reverse" },
      { GTK_PRINT_CAPABILITY_SCALE, "GTK_PRINT_CAPABILITY_SCALE", "scale" },
      { 0, NULL, NULL }
    };
    etype = g_flags_register_static (g_intern_static_string ("GtkPrintCapabilites"), values);
  }
  return etype;
}
#endif

 
void
pygtk_custom_destroy_notify(gpointer user_data)
{
    PyGtkCustomNotify *cunote = user_data;
    PyGILState_STATE state;
 
    g_return_if_fail(user_data);
    state = pyg_gil_state_ensure();
    Py_XDECREF(cunote->func);
    Py_XDECREF(cunote->data);
    pyg_gil_state_release(state);
     
    g_free(cunote);
}


#line 76 "gtkunixprint.c"


/* ---------- types from other modules ---------- */
static PyTypeObject *_PyGObject_Type;
#define PyGObject_Type (*_PyGObject_Type)
static PyTypeObject *_PyGtkDialog_Type;
#define PyGtkDialog_Type (*_PyGtkDialog_Type)
static PyTypeObject *_PyGtkPageSetup_Type;
#define PyGtkPageSetup_Type (*_PyGtkPageSetup_Type)
static PyTypeObject *_PyGtkPrintSettings_Type;
#define PyGtkPrintSettings_Type (*_PyGtkPrintSettings_Type)
static PyTypeObject *_PyGtkWidget_Type;
#define PyGtkWidget_Type (*_PyGtkWidget_Type)
static PyTypeObject *_PyGtkWindow_Type;
#define PyGtkWindow_Type (*_PyGtkWindow_Type)


/* ---------- forward type declarations ---------- */
PyTypeObject G_GNUC_INTERNAL PyGtkPageSetupUnixDialog_Type;
PyTypeObject G_GNUC_INTERNAL PyGtkPrintJob_Type;
PyTypeObject G_GNUC_INTERNAL PyGtkPrintUnixDialog_Type;
PyTypeObject G_GNUC_INTERNAL PyGtkPrinter_Type;

#line 100 "gtkunixprint.c"



/* ----------- GtkPageSetupUnixDialog ----------- */

static int
_wrap_gtk_page_setup_unix_dialog_new(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "title", "parent", NULL };
    char *title = NULL;
    PyGObject *py_parent = NULL;
    GtkWindow *parent = NULL;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs,"|zO:Unixprint.PageSetupUnixDialog.__init__", kwlist, &title, &py_parent))
        return -1;
    if ((PyObject *)py_parent == Py_None)
        parent = NULL;
    else if (py_parent && pygobject_check(py_parent, &PyGtkWindow_Type))
        parent = GTK_WINDOW(py_parent->obj);
    else if (py_parent) {
        PyErr_SetString(PyExc_TypeError, "parent should be a GtkWindow or None");
        return -1;
    }
    self->obj = (GObject *)gtk_page_setup_unix_dialog_new(title, (GtkWindow *) parent);

    if (!self->obj) {
        PyErr_SetString(PyExc_RuntimeError, "could not create GtkPageSetupUnixDialog object");
        return -1;
    }
    pygobject_register_wrapper((PyObject *)self);
    return 0;
}

static PyObject *
_wrap_gtk_page_setup_unix_dialog_set_page_setup(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "page_setup", NULL };
    PyGObject *page_setup;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs,"O!:Unixprint.PageSetupUnixDialog.set_page_setup", kwlist, &PyGtkPageSetup_Type, &page_setup))
        return NULL;
    
    gtk_page_setup_unix_dialog_set_page_setup(GTK_PAGE_SETUP_UNIX_DIALOG(self->obj), GTK_PAGE_SETUP(page_setup->obj));
    
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_gtk_page_setup_unix_dialog_get_page_setup(PyGObject *self)
{
    GtkPageSetup *ret;

    
    ret = gtk_page_setup_unix_dialog_get_page_setup(GTK_PAGE_SETUP_UNIX_DIALOG(self->obj));
    
    /* pygobject_new handles NULL checking */
    return pygobject_new((GObject *)ret);
}

static PyObject *
_wrap_gtk_page_setup_unix_dialog_set_print_settings(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "print_settings", NULL };
    PyGObject *print_settings;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs,"O!:Unixprint.PageSetupUnixDialog.set_print_settings", kwlist, &PyGtkPrintSettings_Type, &print_settings))
        return NULL;
    
    gtk_page_setup_unix_dialog_set_print_settings(GTK_PAGE_SETUP_UNIX_DIALOG(self->obj), GTK_PRINT_SETTINGS(print_settings->obj));
    
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_gtk_page_setup_unix_dialog_get_print_settings(PyGObject *self)
{
    GtkPrintSettings *ret;

    
    ret = gtk_page_setup_unix_dialog_get_print_settings(GTK_PAGE_SETUP_UNIX_DIALOG(self->obj));
    
    /* pygobject_new handles NULL checking */
    return pygobject_new((GObject *)ret);
}

static const PyMethodDef _PyGtkPageSetupUnixDialog_methods[] = {
    { "set_page_setup", (PyCFunction)_wrap_gtk_page_setup_unix_dialog_set_page_setup, METH_VARARGS|METH_KEYWORDS,
      NULL },
    { "get_page_setup", (PyCFunction)_wrap_gtk_page_setup_unix_dialog_get_page_setup, METH_NOARGS,
      NULL },
    { "set_print_settings", (PyCFunction)_wrap_gtk_page_setup_unix_dialog_set_print_settings, METH_VARARGS|METH_KEYWORDS,
      NULL },
    { "get_print_settings", (PyCFunction)_wrap_gtk_page_setup_unix_dialog_get_print_settings, METH_NOARGS,
      NULL },
    { NULL, NULL, 0, NULL }
};

PyTypeObject G_GNUC_INTERNAL PyGtkPageSetupUnixDialog_Type = {
    PyObject_HEAD_INIT(NULL)
    0,                                 /* ob_size */
    "gtkunixprint.PageSetupUnixDialog",                   /* tp_name */
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
    (struct PyMethodDef*)_PyGtkPageSetupUnixDialog_methods, /* tp_methods */
    (struct PyMemberDef*)0,              /* tp_members */
    (struct PyGetSetDef*)0,  /* tp_getset */
    NULL,                              /* tp_base */
    NULL,                              /* tp_dict */
    (descrgetfunc)0,    /* tp_descr_get */
    (descrsetfunc)0,    /* tp_descr_set */
    offsetof(PyGObject, inst_dict),                 /* tp_dictoffset */
    (initproc)_wrap_gtk_page_setup_unix_dialog_new,             /* tp_init */
    (allocfunc)0,           /* tp_alloc */
    (newfunc)0,               /* tp_new */
    (freefunc)0,             /* tp_free */
    (inquiry)0              /* tp_is_gc */
};



/* ----------- GtkPrintJob ----------- */

static int
_wrap_gtk_print_job_new(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "title", "printer", "settings", "page_setup", NULL };
    char *title;
    PyGObject *printer, *settings, *page_setup;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs,"sO!O!O!:Unixprint.PrintJob.__init__", kwlist, &title, &PyGtkPrinter_Type, &printer, &PyGtkPrintSettings_Type, &settings, &PyGtkPageSetup_Type, &page_setup))
        return -1;
    self->obj = (GObject *)gtk_print_job_new(title, GTK_PRINTER(printer->obj), GTK_PRINT_SETTINGS(settings->obj), GTK_PAGE_SETUP(page_setup->obj));

    if (!self->obj) {
        PyErr_SetString(PyExc_RuntimeError, "could not create GtkPrintJob object");
        return -1;
    }
    pygobject_register_wrapper((PyObject *)self);
    return 0;
}

static PyObject *
_wrap_gtk_print_job_get_settings(PyGObject *self)
{
    GtkPrintSettings *ret;

    
    ret = gtk_print_job_get_settings(GTK_PRINT_JOB(self->obj));
    
    /* pygobject_new handles NULL checking */
    return pygobject_new((GObject *)ret);
}

static PyObject *
_wrap_gtk_print_job_get_printer(PyGObject *self)
{
    GtkPrinter *ret;

    
    ret = gtk_print_job_get_printer(GTK_PRINT_JOB(self->obj));
    
    /* pygobject_new handles NULL checking */
    return pygobject_new((GObject *)ret);
}

static PyObject *
_wrap_gtk_print_job_get_title(PyGObject *self)
{
    const gchar *ret;

    
    ret = gtk_print_job_get_title(GTK_PRINT_JOB(self->obj));
    
    if (ret)
        return PyString_FromString(ret);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_gtk_print_job_get_status(PyGObject *self)
{
    gint ret;

    
    ret = gtk_print_job_get_status(GTK_PRINT_JOB(self->obj));
    
    return pyg_enum_from_gtype(GTK_TYPE_PRINT_STATUS, ret);
}

static PyObject *
_wrap_gtk_print_job_set_source_file(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "filename", NULL };
    char *filename;
    int ret;
    GError *error = NULL;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs,"s:Unixprint.PrintJob.set_source_file", kwlist, &filename))
        return NULL;
    
    ret = gtk_print_job_set_source_file(GTK_PRINT_JOB(self->obj), filename, &error);
    
    if (pyg_error_check(&error))
        return NULL;
    return PyBool_FromLong(ret);

}

#line 94 "/home/thread/dev/meld/git/threader/meld-1.8/deps/pygtk-2.24/pygtk-2.24.0/gtk/gtkunixprint.override"
static PyObject*
_wrap_gtk_print_job_get_surface(PyGObject *self)
{
    GError *error = NULL;
    cairo_surface_t * surface;

    surface = gtk_print_job_get_surface(GTK_PRINT_JOB(self->obj), &error);

    if (pyg_error_check(&error))
        return NULL;

#if PYCAIRO_VERSION_HEX >= 0x1010600
    return PycairoSurface_FromSurface(cairo_surface_reference(surface), NULL);
#else
    return PycairoSurface_FromSurface(cairo_surface_reference(surface), NULL, NULL);
#endif
}
#line 354 "gtkunixprint.c"


static PyObject *
_wrap_gtk_print_job_set_track_print_status(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "track_status", NULL };
    int track_status;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs,"i:Unixprint.PrintJob.set_track_print_status", kwlist, &track_status))
        return NULL;
    
    gtk_print_job_set_track_print_status(GTK_PRINT_JOB(self->obj), track_status);
    
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_gtk_print_job_get_track_print_status(PyGObject *self)
{
    int ret;

    
    ret = gtk_print_job_get_track_print_status(GTK_PRINT_JOB(self->obj));
    
    return PyBool_FromLong(ret);

}

#line 113 "/home/thread/dev/meld/git/threader/meld-1.8/deps/pygtk-2.24/pygtk-2.24.0/gtk/gtkunixprint.override"
static void
pygtk_print_job_complete_func_cb(GtkPrintJob *print_job, gpointer user_data,
                                 GError *error)
{
    PyGILState_STATE state;
    PyGtkCustomNotify *cunote = user_data;
    PyObject *retobj, *data;
    gchar *errorstr = NULL;
                                                                               
    g_assert(cunote->func);
                                                                               
    state = pyg_gil_state_ensure();
                                                                               
    if (cunote->data)
        data = cunote->data;
    else
        data = Py_None;

    if (error)
        errorstr = error->message;

    retobj = PyEval_CallFunction(cunote->func, "(NOz)",
                                 pygobject_new((GObject *)print_job),
                                 data, errorstr);
                                                                               
    if (retobj == NULL)
        PyErr_Print();

    Py_XDECREF(retobj);
                                                                               
    pyg_gil_state_release(state);
}
static PyObject*
_wrap_gtk_print_job_send(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "callback", "user_data", NULL };
    PyObject *pyfunc, *pyarg = NULL;
    PyGtkCustomNotify *cunote;
  
    if (!PyArg_ParseTupleAndKeywords(args, kwargs,
                                     "O|O:gtkunixprint.PrintJob.send",
                                     kwlist, &pyfunc, &pyarg))
        return NULL;
  
    if (!PyCallable_Check(pyfunc)) {
        PyErr_SetString(PyExc_TypeError, "callback must be a callable object");
        return NULL;
    }
    cunote = g_new0(PyGtkCustomNotify, 1);
    cunote->func = pyfunc;
    cunote->data = pyarg;
    Py_INCREF(cunote->func);
    Py_XINCREF(cunote->data);
 
    gtk_print_job_send(GTK_PRINT_JOB(self->obj),
                             pygtk_print_job_complete_func_cb,
                             cunote, pygtk_custom_destroy_notify);
 
    Py_INCREF(Py_None);
    return Py_None;
}
#line 446 "gtkunixprint.c"


static PyObject *
_wrap_GtkPrintJob__do_status_changed(PyObject *cls, PyObject *args, PyObject *kwargs)
{
    gpointer klass;
    static char *kwlist[] = { "self", NULL };
    PyGObject *self;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs,"O!:Unixprint.PrintJob.status_changed", kwlist, &PyGtkPrintJob_Type, &self))
        return NULL;
    klass = g_type_class_ref(pyg_type_from_object(cls));
    if (GTK_PRINT_JOB_CLASS(klass)->status_changed)
        GTK_PRINT_JOB_CLASS(klass)->status_changed(GTK_PRINT_JOB(self->obj));
    else {
        PyErr_SetString(PyExc_NotImplementedError, "virtual method Unixprint.PrintJob.status_changed not implemented");
        g_type_class_unref(klass);
        return NULL;
    }
    g_type_class_unref(klass);
    Py_INCREF(Py_None);
    return Py_None;
}

static const PyMethodDef _PyGtkPrintJob_methods[] = {
    { "get_settings", (PyCFunction)_wrap_gtk_print_job_get_settings, METH_NOARGS,
      NULL },
    { "get_printer", (PyCFunction)_wrap_gtk_print_job_get_printer, METH_NOARGS,
      NULL },
    { "get_title", (PyCFunction)_wrap_gtk_print_job_get_title, METH_NOARGS,
      NULL },
    { "get_status", (PyCFunction)_wrap_gtk_print_job_get_status, METH_NOARGS,
      NULL },
    { "set_source_file", (PyCFunction)_wrap_gtk_print_job_set_source_file, METH_VARARGS|METH_KEYWORDS,
      NULL },
    { "get_surface", (PyCFunction)_wrap_gtk_print_job_get_surface, METH_NOARGS,
      NULL },
    { "set_track_print_status", (PyCFunction)_wrap_gtk_print_job_set_track_print_status, METH_VARARGS|METH_KEYWORDS,
      NULL },
    { "get_track_print_status", (PyCFunction)_wrap_gtk_print_job_get_track_print_status, METH_NOARGS,
      NULL },
    { "send", (PyCFunction)_wrap_gtk_print_job_send, METH_VARARGS|METH_KEYWORDS,
      NULL },
    { "do_status_changed", (PyCFunction)_wrap_GtkPrintJob__do_status_changed, METH_VARARGS|METH_KEYWORDS|METH_CLASS,
      NULL },
    { NULL, NULL, 0, NULL }
};

PyTypeObject G_GNUC_INTERNAL PyGtkPrintJob_Type = {
    PyObject_HEAD_INIT(NULL)
    0,                                 /* ob_size */
    "gtkunixprint.PrintJob",                   /* tp_name */
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
    (struct PyMethodDef*)_PyGtkPrintJob_methods, /* tp_methods */
    (struct PyMemberDef*)0,              /* tp_members */
    (struct PyGetSetDef*)0,  /* tp_getset */
    NULL,                              /* tp_base */
    NULL,                              /* tp_dict */
    (descrgetfunc)0,    /* tp_descr_get */
    (descrsetfunc)0,    /* tp_descr_set */
    offsetof(PyGObject, inst_dict),                 /* tp_dictoffset */
    (initproc)_wrap_gtk_print_job_new,             /* tp_init */
    (allocfunc)0,           /* tp_alloc */
    (newfunc)0,               /* tp_new */
    (freefunc)0,             /* tp_free */
    (inquiry)0              /* tp_is_gc */
};

static void
_wrap_GtkPrintJob__proxy_do_status_changed(GtkPrintJob *self)
{
    PyGILState_STATE __py_state;
    PyObject *py_self;
    PyObject *py_retval;
    PyObject *py_method;
    
    __py_state = pyg_gil_state_ensure();
    py_self = pygobject_new((GObject *) self);
    if (!py_self) {
        if (PyErr_Occurred())
            PyErr_Print();
        pyg_gil_state_release(__py_state);
        return;
    }
    
    
    py_method = PyObject_GetAttrString(py_self, "do_status_changed");
    if (!py_method) {
        if (PyErr_Occurred())
            PyErr_Print();
        Py_DECREF(py_self);
        pyg_gil_state_release(__py_state);
        return;
    }
    py_retval = PyObject_CallObject(py_method, NULL);
    if (!py_retval) {
        if (PyErr_Occurred())
            PyErr_Print();
        Py_XDECREF(py_retval);
        Py_DECREF(py_method);
        Py_DECREF(py_self);
        pyg_gil_state_release(__py_state);
        return;
    }
    if (py_retval != Py_None) {
        PyErr_SetString(PyExc_TypeError, "virtual method should return None");
        PyErr_Print();
        Py_XDECREF(py_retval);
        Py_DECREF(py_method);
        Py_DECREF(py_self);
        pyg_gil_state_release(__py_state);
        return;
    }
    
    
    Py_XDECREF(py_retval);
    Py_DECREF(py_method);
    Py_DECREF(py_self);
    pyg_gil_state_release(__py_state);
}

static int
__GtkPrintJob_class_init(gpointer gclass, PyTypeObject *pyclass)
{
    PyObject *o;
    GtkPrintJobClass *klass = GTK_PRINT_JOB_CLASS(gclass);
    PyObject *gsignals = PyDict_GetItemString(pyclass->tp_dict, "__gsignals__");

    o = PyObject_GetAttrString((PyObject *) pyclass, "do_status_changed");
    if (o == NULL)
        PyErr_Clear();
    else {
        if (!PyObject_TypeCheck(o, &PyCFunction_Type)
            && !(gsignals && PyDict_GetItemString(gsignals, "status_changed")))
            klass->status_changed = _wrap_GtkPrintJob__proxy_do_status_changed;
        Py_DECREF(o);
    }
    return 0;
}


/* ----------- GtkPrintUnixDialog ----------- */

static int
_wrap_gtk_print_unix_dialog_new(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "title", "parent", NULL };
    char *title = NULL;
    PyGObject *py_parent = NULL;
    GtkWindow *parent = NULL;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs,"|zO:Unixprint.PrintUnixDialog.__init__", kwlist, &title, &py_parent))
        return -1;
    if ((PyObject *)py_parent == Py_None)
        parent = NULL;
    else if (py_parent && pygobject_check(py_parent, &PyGtkWindow_Type))
        parent = GTK_WINDOW(py_parent->obj);
    else if (py_parent) {
        PyErr_SetString(PyExc_TypeError, "parent should be a GtkWindow or None");
        return -1;
    }
    self->obj = (GObject *)gtk_print_unix_dialog_new(title, (GtkWindow *) parent);

    if (!self->obj) {
        PyErr_SetString(PyExc_RuntimeError, "could not create GtkPrintUnixDialog object");
        return -1;
    }
    pygobject_register_wrapper((PyObject *)self);
    return 0;
}

static PyObject *
_wrap_gtk_print_unix_dialog_set_page_setup(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "page_setup", NULL };
    PyGObject *page_setup;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs,"O!:Unixprint.PrintUnixDialog.set_page_setup", kwlist, &PyGtkPageSetup_Type, &page_setup))
        return NULL;
    
    gtk_print_unix_dialog_set_page_setup(GTK_PRINT_UNIX_DIALOG(self->obj), GTK_PAGE_SETUP(page_setup->obj));
    
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_gtk_print_unix_dialog_get_page_setup(PyGObject *self)
{
    GtkPageSetup *ret;

    
    ret = gtk_print_unix_dialog_get_page_setup(GTK_PRINT_UNIX_DIALOG(self->obj));
    
    /* pygobject_new handles NULL checking */
    return pygobject_new((GObject *)ret);
}

static PyObject *
_wrap_gtk_print_unix_dialog_set_current_page(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "current_page", NULL };
    int current_page;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs,"i:Unixprint.PrintUnixDialog.set_current_page", kwlist, &current_page))
        return NULL;
    
    gtk_print_unix_dialog_set_current_page(GTK_PRINT_UNIX_DIALOG(self->obj), current_page);
    
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_gtk_print_unix_dialog_get_current_page(PyGObject *self)
{
    int ret;

    
    ret = gtk_print_unix_dialog_get_current_page(GTK_PRINT_UNIX_DIALOG(self->obj));
    
    return PyInt_FromLong(ret);
}

static PyObject *
_wrap_gtk_print_unix_dialog_set_settings(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "settings", NULL };
    PyGObject *py_settings = NULL;
    GtkPrintSettings *settings = NULL;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs,"|O:Unixprint.PrintUnixDialog.set_settings", kwlist, &py_settings))
        return NULL;
    if ((PyObject *)py_settings == Py_None)
        settings = NULL;
    else if (py_settings && pygobject_check(py_settings, &PyGtkPrintSettings_Type))
        settings = GTK_PRINT_SETTINGS(py_settings->obj);
    else if (py_settings) {
        PyErr_SetString(PyExc_TypeError, "settings should be a GtkPrintSettings or None");
        return NULL;
    }
    
    gtk_print_unix_dialog_set_settings(GTK_PRINT_UNIX_DIALOG(self->obj), (GtkPrintSettings *) settings);
    
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_gtk_print_unix_dialog_get_settings(PyGObject *self)
{
    GtkPrintSettings *ret;

    
    ret = gtk_print_unix_dialog_get_settings(GTK_PRINT_UNIX_DIALOG(self->obj));
    
    /* pygobject_new handles NULL checking */
    return pygobject_new((GObject *)ret);
}

static PyObject *
_wrap_gtk_print_unix_dialog_get_selected_printer(PyGObject *self)
{
    GtkPrinter *ret;

    
    ret = gtk_print_unix_dialog_get_selected_printer(GTK_PRINT_UNIX_DIALOG(self->obj));
    
    /* pygobject_new handles NULL checking */
    return pygobject_new((GObject *)ret);
}

static PyObject *
_wrap_gtk_print_unix_dialog_add_custom_tab(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "child", "tab_label", NULL };
    PyGObject *child, *tab_label;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs,"O!O!:Unixprint.PrintUnixDialog.add_custom_tab", kwlist, &PyGtkWidget_Type, &child, &PyGtkWidget_Type, &tab_label))
        return NULL;
    
    gtk_print_unix_dialog_add_custom_tab(GTK_PRINT_UNIX_DIALOG(self->obj), GTK_WIDGET(child->obj), GTK_WIDGET(tab_label->obj));
    
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_gtk_print_unix_dialog_set_manual_capabilities(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "capabilities", NULL };
    PyObject *py_capabilities = NULL;
    GtkPrintCapabilities capabilities;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs,"O:Unixprint.PrintUnixDialog.set_manual_capabilities", kwlist, &py_capabilities))
        return NULL;
    if (pyg_flags_get_value(GTK_TYPE_PRINT_CAPABILITIES, py_capabilities, (gpointer)&capabilities))
        return NULL;
    
    gtk_print_unix_dialog_set_manual_capabilities(GTK_PRINT_UNIX_DIALOG(self->obj), capabilities);
    
    Py_INCREF(Py_None);
    return Py_None;
}

static const PyMethodDef _PyGtkPrintUnixDialog_methods[] = {
    { "set_page_setup", (PyCFunction)_wrap_gtk_print_unix_dialog_set_page_setup, METH_VARARGS|METH_KEYWORDS,
      NULL },
    { "get_page_setup", (PyCFunction)_wrap_gtk_print_unix_dialog_get_page_setup, METH_NOARGS,
      NULL },
    { "set_current_page", (PyCFunction)_wrap_gtk_print_unix_dialog_set_current_page, METH_VARARGS|METH_KEYWORDS,
      NULL },
    { "get_current_page", (PyCFunction)_wrap_gtk_print_unix_dialog_get_current_page, METH_NOARGS,
      NULL },
    { "set_settings", (PyCFunction)_wrap_gtk_print_unix_dialog_set_settings, METH_VARARGS|METH_KEYWORDS,
      NULL },
    { "get_settings", (PyCFunction)_wrap_gtk_print_unix_dialog_get_settings, METH_NOARGS,
      NULL },
    { "get_selected_printer", (PyCFunction)_wrap_gtk_print_unix_dialog_get_selected_printer, METH_NOARGS,
      NULL },
    { "add_custom_tab", (PyCFunction)_wrap_gtk_print_unix_dialog_add_custom_tab, METH_VARARGS|METH_KEYWORDS,
      NULL },
    { "set_manual_capabilities", (PyCFunction)_wrap_gtk_print_unix_dialog_set_manual_capabilities, METH_VARARGS|METH_KEYWORDS,
      NULL },
    { NULL, NULL, 0, NULL }
};

PyTypeObject G_GNUC_INTERNAL PyGtkPrintUnixDialog_Type = {
    PyObject_HEAD_INIT(NULL)
    0,                                 /* ob_size */
    "gtkunixprint.PrintUnixDialog",                   /* tp_name */
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
    (struct PyMethodDef*)_PyGtkPrintUnixDialog_methods, /* tp_methods */
    (struct PyMemberDef*)0,              /* tp_members */
    (struct PyGetSetDef*)0,  /* tp_getset */
    NULL,                              /* tp_base */
    NULL,                              /* tp_dict */
    (descrgetfunc)0,    /* tp_descr_get */
    (descrsetfunc)0,    /* tp_descr_set */
    offsetof(PyGObject, inst_dict),                 /* tp_dictoffset */
    (initproc)_wrap_gtk_print_unix_dialog_new,             /* tp_init */
    (allocfunc)0,           /* tp_alloc */
    (newfunc)0,               /* tp_new */
    (freefunc)0,             /* tp_free */
    (inquiry)0              /* tp_is_gc */
};



/* ----------- GtkPrinter ----------- */

static int
pygobject_no_constructor(PyObject *self, PyObject *args, PyObject *kwargs)
{
    gchar buf[512];

    g_snprintf(buf, sizeof(buf), "%s is an abstract widget", self->ob_type->tp_name);
    PyErr_SetString(PyExc_NotImplementedError, buf);
    return -1;
}

static PyObject *
_wrap_gtk_printer_get_name(PyGObject *self)
{
    const gchar *ret;

    
    ret = gtk_printer_get_name(GTK_PRINTER(self->obj));
    
    if (ret)
        return PyString_FromString(ret);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_gtk_printer_get_state_message(PyGObject *self)
{
    const gchar *ret;

    
    ret = gtk_printer_get_state_message(GTK_PRINTER(self->obj));
    
    if (ret)
        return PyString_FromString(ret);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_gtk_printer_get_description(PyGObject *self)
{
    const gchar *ret;

    
    ret = gtk_printer_get_description(GTK_PRINTER(self->obj));
    
    if (ret)
        return PyString_FromString(ret);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_gtk_printer_get_location(PyGObject *self)
{
    const gchar *ret;

    
    ret = gtk_printer_get_location(GTK_PRINTER(self->obj));
    
    if (ret)
        return PyString_FromString(ret);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_gtk_printer_get_icon_name(PyGObject *self)
{
    const gchar *ret;

    
    ret = gtk_printer_get_icon_name(GTK_PRINTER(self->obj));
    
    if (ret)
        return PyString_FromString(ret);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_gtk_printer_get_job_count(PyGObject *self)
{
    int ret;

    
    ret = gtk_printer_get_job_count(GTK_PRINTER(self->obj));
    
    return PyInt_FromLong(ret);
}

static PyObject *
_wrap_gtk_printer_is_active(PyGObject *self)
{
    int ret;

    
    ret = gtk_printer_is_active(GTK_PRINTER(self->obj));
    
    return PyBool_FromLong(ret);

}

static PyObject *
_wrap_gtk_printer_is_virtual(PyGObject *self)
{
    int ret;

    
    ret = gtk_printer_is_virtual(GTK_PRINTER(self->obj));
    
    return PyBool_FromLong(ret);

}

static PyObject *
_wrap_gtk_printer_is_default(PyGObject *self)
{
    int ret;

    
    ret = gtk_printer_is_default(GTK_PRINTER(self->obj));
    
    return PyBool_FromLong(ret);

}

static PyObject *
_wrap_gtk_printer_accepts_pdf(PyGObject *self)
{
    int ret;

    
    ret = gtk_printer_accepts_pdf(GTK_PRINTER(self->obj));
    
    return PyBool_FromLong(ret);

}

static PyObject *
_wrap_gtk_printer_accepts_ps(PyGObject *self)
{
    int ret;

    
    ret = gtk_printer_accepts_ps(GTK_PRINTER(self->obj));
    
    return PyBool_FromLong(ret);

}

static PyObject *
_wrap_gtk_printer_compare(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "b", NULL };
    PyGObject *b;
    int ret;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs,"O!:Unixprint.Printer.compare", kwlist, &PyGtkPrinter_Type, &b))
        return NULL;
    
    ret = gtk_printer_compare(GTK_PRINTER(self->obj), GTK_PRINTER(b->obj));
    
    return PyInt_FromLong(ret);
}

#line 236 "/home/thread/dev/meld/git/threader/meld-1.8/deps/pygtk-2.24/pygtk-2.24.0/gtk/gtkunixprint.override"
static PyObject*
_wrap_gtk_printer_list_papers(PyGObject *self)
{
    GList *list;
    PyObject *ret;

    list = gtk_printer_list_papers(GTK_PRINTER(self->obj));

    if (list) {
        PYLIST_FROMGLIST(ret, list, pygobject_new(list_item), NULL, NULL);
        return ret;
    } else {
        Py_INCREF(Py_None);
        return Py_None;
    }
}
#line 1031 "gtkunixprint.c"


static PyObject *
_wrap_gtk_printer_has_details(PyGObject *self)
{
    int ret;

    
    ret = gtk_printer_has_details(GTK_PRINTER(self->obj));
    
    return PyBool_FromLong(ret);

}

static PyObject *
_wrap_gtk_printer_request_details(PyGObject *self)
{
    
    gtk_printer_request_details(GTK_PRINTER(self->obj));
    
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_gtk_printer_get_capabilities(PyGObject *self)
{
    guint ret;

    
    ret = gtk_printer_get_capabilities(GTK_PRINTER(self->obj));
    
    return pyg_flags_from_gtype(GTK_TYPE_PRINT_CAPABILITIES, ret);
}

static PyObject *
_wrap_gtk_printer_is_paused(PyGObject *self)
{
    int ret;

    
    ret = gtk_printer_is_paused(GTK_PRINTER(self->obj));
    
    return PyBool_FromLong(ret);

}

static PyObject *
_wrap_gtk_printer_is_accepting_jobs(PyGObject *self)
{
    int ret;

    
    ret = gtk_printer_is_accepting_jobs(GTK_PRINTER(self->obj));
    
    return PyBool_FromLong(ret);

}

static PyObject *
_wrap_GtkPrinter__do_details_acquired(PyObject *cls, PyObject *args, PyObject *kwargs)
{
    gpointer klass;
    static char *kwlist[] = { "self", "success", NULL };
    PyGObject *self;
    int success;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs,"O!i:Unixprint.Printer.details_acquired", kwlist, &PyGtkPrinter_Type, &self, &success))
        return NULL;
    klass = g_type_class_ref(pyg_type_from_object(cls));
    if (GTK_PRINTER_CLASS(klass)->details_acquired)
        GTK_PRINTER_CLASS(klass)->details_acquired(GTK_PRINTER(self->obj), success);
    else {
        PyErr_SetString(PyExc_NotImplementedError, "virtual method Unixprint.Printer.details_acquired not implemented");
        g_type_class_unref(klass);
        return NULL;
    }
    g_type_class_unref(klass);
    Py_INCREF(Py_None);
    return Py_None;
}

static const PyMethodDef _PyGtkPrinter_methods[] = {
    { "get_name", (PyCFunction)_wrap_gtk_printer_get_name, METH_NOARGS,
      NULL },
    { "get_state_message", (PyCFunction)_wrap_gtk_printer_get_state_message, METH_NOARGS,
      NULL },
    { "get_description", (PyCFunction)_wrap_gtk_printer_get_description, METH_NOARGS,
      NULL },
    { "get_location", (PyCFunction)_wrap_gtk_printer_get_location, METH_NOARGS,
      NULL },
    { "get_icon_name", (PyCFunction)_wrap_gtk_printer_get_icon_name, METH_NOARGS,
      NULL },
    { "get_job_count", (PyCFunction)_wrap_gtk_printer_get_job_count, METH_NOARGS,
      NULL },
    { "is_active", (PyCFunction)_wrap_gtk_printer_is_active, METH_NOARGS,
      NULL },
    { "is_virtual", (PyCFunction)_wrap_gtk_printer_is_virtual, METH_NOARGS,
      NULL },
    { "is_default", (PyCFunction)_wrap_gtk_printer_is_default, METH_NOARGS,
      NULL },
    { "accepts_pdf", (PyCFunction)_wrap_gtk_printer_accepts_pdf, METH_NOARGS,
      NULL },
    { "accepts_ps", (PyCFunction)_wrap_gtk_printer_accepts_ps, METH_NOARGS,
      NULL },
    { "compare", (PyCFunction)_wrap_gtk_printer_compare, METH_VARARGS|METH_KEYWORDS,
      NULL },
    { "list_papers", (PyCFunction)_wrap_gtk_printer_list_papers, METH_NOARGS,
      NULL },
    { "has_details", (PyCFunction)_wrap_gtk_printer_has_details, METH_NOARGS,
      NULL },
    { "request_details", (PyCFunction)_wrap_gtk_printer_request_details, METH_NOARGS,
      NULL },
    { "get_capabilities", (PyCFunction)_wrap_gtk_printer_get_capabilities, METH_NOARGS,
      NULL },
    { "is_paused", (PyCFunction)_wrap_gtk_printer_is_paused, METH_NOARGS,
      NULL },
    { "is_accepting_jobs", (PyCFunction)_wrap_gtk_printer_is_accepting_jobs, METH_NOARGS,
      NULL },
    { "do_details_acquired", (PyCFunction)_wrap_GtkPrinter__do_details_acquired, METH_VARARGS|METH_KEYWORDS|METH_CLASS,
      NULL },
    { NULL, NULL, 0, NULL }
};

PyTypeObject G_GNUC_INTERNAL PyGtkPrinter_Type = {
    PyObject_HEAD_INIT(NULL)
    0,                                 /* ob_size */
    "gtkunixprint.Printer",                   /* tp_name */
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
    (struct PyMethodDef*)_PyGtkPrinter_methods, /* tp_methods */
    (struct PyMemberDef*)0,              /* tp_members */
    (struct PyGetSetDef*)0,  /* tp_getset */
    NULL,                              /* tp_base */
    NULL,                              /* tp_dict */
    (descrgetfunc)0,    /* tp_descr_get */
    (descrsetfunc)0,    /* tp_descr_set */
    offsetof(PyGObject, inst_dict),                 /* tp_dictoffset */
    (initproc)pygobject_no_constructor,             /* tp_init */
    (allocfunc)0,           /* tp_alloc */
    (newfunc)0,               /* tp_new */
    (freefunc)0,             /* tp_free */
    (inquiry)0              /* tp_is_gc */
};

static void
_wrap_GtkPrinter__proxy_do_details_acquired(GtkPrinter *self, gboolean success)
{
    PyGILState_STATE __py_state;
    PyObject *py_self;
    PyObject *py_success;
    PyObject *py_retval;
    PyObject *py_args;
    PyObject *py_method;
    
    __py_state = pyg_gil_state_ensure();
    py_self = pygobject_new((GObject *) self);
    if (!py_self) {
        if (PyErr_Occurred())
            PyErr_Print();
        pyg_gil_state_release(__py_state);
        return;
    }
    py_success = success? Py_True : Py_False;
    
    py_args = PyTuple_New(1);
    Py_INCREF(py_success);
    PyTuple_SET_ITEM(py_args, 0, py_success);
    
    py_method = PyObject_GetAttrString(py_self, "do_details_acquired");
    if (!py_method) {
        if (PyErr_Occurred())
            PyErr_Print();
        Py_DECREF(py_args);
        Py_DECREF(py_self);
        pyg_gil_state_release(__py_state);
        return;
    }
    py_retval = PyObject_CallObject(py_method, py_args);
    if (!py_retval) {
        if (PyErr_Occurred())
            PyErr_Print();
        Py_XDECREF(py_retval);
        Py_DECREF(py_method);
        Py_DECREF(py_args);
        Py_DECREF(py_self);
        pyg_gil_state_release(__py_state);
        return;
    }
    if (py_retval != Py_None) {
        PyErr_SetString(PyExc_TypeError, "virtual method should return None");
        PyErr_Print();
        Py_XDECREF(py_retval);
        Py_DECREF(py_method);
        Py_DECREF(py_args);
        Py_DECREF(py_self);
        pyg_gil_state_release(__py_state);
        return;
    }
    
    
    Py_XDECREF(py_retval);
    Py_DECREF(py_method);
    Py_DECREF(py_args);
    Py_DECREF(py_self);
    pyg_gil_state_release(__py_state);
}

static int
__GtkPrinter_class_init(gpointer gclass, PyTypeObject *pyclass)
{
    PyObject *o;
    GtkPrinterClass *klass = GTK_PRINTER_CLASS(gclass);
    PyObject *gsignals = PyDict_GetItemString(pyclass->tp_dict, "__gsignals__");

    o = PyObject_GetAttrString((PyObject *) pyclass, "do_details_acquired");
    if (o == NULL)
        PyErr_Clear();
    else {
        if (!PyObject_TypeCheck(o, &PyCFunction_Type)
            && !(gsignals && PyDict_GetItemString(gsignals, "details_acquired")))
            klass->details_acquired = _wrap_GtkPrinter__proxy_do_details_acquired;
        Py_DECREF(o);
    }
    return 0;
}


/* ----------- functions ----------- */

#line 176 "/home/thread/dev/meld/git/threader/meld-1.8/deps/pygtk-2.24/pygtk-2.24.0/gtk/gtkunixprint.override"
static gboolean
pygtk_printer_func_cb(GtkPrinter *printer, gpointer user_data)
{
    PyGILState_STATE state;
    PyGtkCustomNotify *cunote = user_data;
    PyObject *retobj;
    gboolean ret = TRUE;
                                                                               
    g_assert(cunote->func);
    state = pyg_gil_state_ensure();
                                                                               
    if (cunote->data)
        retobj = PyEval_CallFunction(cunote->func, "(NO)",
                                     pygobject_new((GObject *)printer),
                                     cunote->data);
   else
        retobj = PyEval_CallFunction(cunote->func, "(N)",
                                     pygobject_new((GObject *)printer));
                                                                               
    if (retobj == NULL)
        PyErr_Print();
    else if (retobj == Py_False)
        ret = FALSE;

    Py_XDECREF(retobj);
    pyg_gil_state_release(state);
                                                                               
    return ret;
}
static PyObject*
_wrap_gtk_enumerate_printers(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "func", "data", "wait",  NULL };
    PyObject *pyfunc, *pyarg = NULL;
    PyGtkCustomNotify *cunote;
    gboolean wait = TRUE;
  
    if (!PyArg_ParseTupleAndKeywords(args, kwargs,
                                     "O|Oi:gtkunixprint.enumerate_printers",
                                     kwlist, &pyfunc, &pyarg, &wait))
        return NULL;
  
    if (!PyCallable_Check(pyfunc)) {
        PyErr_SetString(PyExc_TypeError, "func must be a callable object");
        return NULL;
    }
    cunote = g_new0(PyGtkCustomNotify, 1);
    cunote->func = pyfunc;
    cunote->data = pyarg;
    Py_INCREF(cunote->func);
    Py_XINCREF(cunote->data);
 
    gtk_enumerate_printers(pygtk_printer_func_cb, cunote,
                           pygtk_custom_destroy_notify, wait);
 
    Py_INCREF(Py_None);
    return Py_None;
}
#line 1345 "gtkunixprint.c"


const PyMethodDef pygtkunixprint_functions[] = {
    { "enumerate_printers", (PyCFunction)_wrap_gtk_enumerate_printers, METH_VARARGS|METH_KEYWORDS,
      NULL },
    { NULL, NULL, 0, NULL }
};


/* ----------- enums and flags ----------- */

void
pygtkunixprint_add_constants(PyObject *module, const gchar *strip_prefix)
{
#ifdef VERSION
    PyModule_AddStringConstant(module, "__version__", VERSION);
#endif
  pyg_flags_add(module, "PrintCapabilities", strip_prefix, GTK_TYPE_PRINT_CAPABILITIES);

  if (PyErr_Occurred())
    PyErr_Print();
}

/* initialise stuff extension classes */
void
pygtkunixprint_register_classes(PyObject *d)
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
        _PyGtkDialog_Type = (PyTypeObject *)PyObject_GetAttrString(module, "Dialog");
        if (_PyGtkDialog_Type == NULL) {
            PyErr_SetString(PyExc_ImportError,
                "cannot import name Dialog from gtk");
            return ;
        }
        _PyGtkPageSetup_Type = (PyTypeObject *)PyObject_GetAttrString(module, "PageSetup");
        if (_PyGtkPageSetup_Type == NULL) {
            PyErr_SetString(PyExc_ImportError,
                "cannot import name PageSetup from gtk");
            return ;
        }
        _PyGtkPrintSettings_Type = (PyTypeObject *)PyObject_GetAttrString(module, "PrintSettings");
        if (_PyGtkPrintSettings_Type == NULL) {
            PyErr_SetString(PyExc_ImportError,
                "cannot import name PrintSettings from gtk");
            return ;
        }
        _PyGtkWidget_Type = (PyTypeObject *)PyObject_GetAttrString(module, "Widget");
        if (_PyGtkWidget_Type == NULL) {
            PyErr_SetString(PyExc_ImportError,
                "cannot import name Widget from gtk");
            return ;
        }
        _PyGtkWindow_Type = (PyTypeObject *)PyObject_GetAttrString(module, "Window");
        if (_PyGtkWindow_Type == NULL) {
            PyErr_SetString(PyExc_ImportError,
                "cannot import name Window from gtk");
            return ;
        }
    } else {
        PyErr_SetString(PyExc_ImportError,
            "could not import gtk");
        return ;
    }


#line 1425 "gtkunixprint.c"
    pygobject_register_class(d, "GtkPageSetupUnixDialog", GTK_TYPE_PAGE_SETUP_UNIX_DIALOG, &PyGtkPageSetupUnixDialog_Type, Py_BuildValue("(O)", &PyGtkDialog_Type));
    pygobject_register_class(d, "GtkPrintJob", GTK_TYPE_PRINT_JOB, &PyGtkPrintJob_Type, Py_BuildValue("(O)", &PyGObject_Type));
    pyg_register_class_init(GTK_TYPE_PRINT_JOB, __GtkPrintJob_class_init);
    pygobject_register_class(d, "GtkPrintUnixDialog", GTK_TYPE_PRINT_UNIX_DIALOG, &PyGtkPrintUnixDialog_Type, Py_BuildValue("(O)", &PyGtkDialog_Type));
    pygobject_register_class(d, "GtkPrinter", GTK_TYPE_PRINTER, &PyGtkPrinter_Type, Py_BuildValue("(O)", &PyGObject_Type));
    pyg_register_class_init(GTK_TYPE_PRINTER, __GtkPrinter_class_init);
}
