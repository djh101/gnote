/*
 * gnote
 *
 * Copyright (C) 2010,2012-2013,2017 Aurimas Cernius
 * Copyright (C) 2009 Hubert Figuiere
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 */




#ifndef __SHARP_ADDINSTREEMODEL_HPP_
#define __SHARP_ADDINSTREEMODEL_HPP_

#include <gtkmm/treestore.h>
#include <gtkmm/treeview.h>

#include "addininfo.hpp"
#include "sharp/dynamicmodule.hpp"

namespace sharp {

class AddinsTreeModel
  : public Gtk::TreeStore
{
public:
  typedef Glib::RefPtr<AddinsTreeModel> Ptr;
  static Ptr create(Gtk::TreeView * treeview);

  Glib::ustring get_module_id(const Gtk::TreeIter &);
  sharp::DynamicModule * get_module(const Gtk::TreeIter &);
  void set_module(const Gtk::TreeIter &, const sharp::DynamicModule *);

  Gtk::TreeIter append(const gnote::AddinInfo &, const sharp::DynamicModule *);
  class AddinsColumns
    : public Gtk::TreeModelColumnRecord
  {
  public:
    AddinsColumns()
      {
        add(name);
        add(version);
        add(addin);
        add(category);
        add(id);
      }

    Gtk::TreeModelColumn<Glib::ustring>          name;
    Gtk::TreeModelColumn<Glib::ustring>          version;
    Gtk::TreeModelColumn<const sharp::DynamicModule *> addin;
    Gtk::TreeModelColumn<gnote::AddinCategory> category;
    Gtk::TreeModelColumn<Glib::ustring>          id;
  };
  AddinsColumns m_columns;

  static Glib::ustring get_addin_category_name(gnote::AddinCategory category);
protected:
  AddinsTreeModel();
  void set_columns(Gtk::TreeView *v);
private:
  void name_cell_data_func(Gtk::CellRenderer * renderer, const Gtk::TreeIter & iter);
  void name_pixbuf_cell_data_func(Gtk::CellRenderer * renderer, const Gtk::TreeIter & iter);
};

}


#endif
