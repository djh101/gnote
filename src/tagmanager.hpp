/*
 * gnote
 *
 * Copyright (C) 2013,2017 Aurimas Cernius
 * Copyright (C) 2009 Hubert Figuiere
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */




#ifndef __TAG_MANAGER_HPP_
#define __TAG_MANAGER_HPP_


#include <sigc++/signal.h>

#include <glibmm/thread.h>
#include <gtkmm/liststore.h>
#include <gtkmm/treemodelsort.h>

#include "base/macros.hpp"
#include "itagmanager.hpp"
#include "tag.hpp"


namespace gnote {

class TagManager
  : public ITagManager
{
public:
  TagManager();

  virtual Tag::Ptr get_tag(const Glib::ustring & tag_name) const override;
  virtual Tag::Ptr get_or_create_tag(const Glib::ustring &) override;
  virtual Tag::Ptr get_system_tag(const Glib::ustring & tag_name) const override;
  virtual Tag::Ptr get_or_create_system_tag(const Glib::ustring & name) override;
  virtual void remove_tag(const Tag::Ptr & tag) override;
  Glib::RefPtr<Gtk::TreeModel> get_tags() const
    {
      return m_sorted_tags;
    }
  virtual void all_tags(std::list<Tag::Ptr> &) const override;
private:
  class ColumnRecord
    : public Gtk::TreeModelColumnRecord
  {
  public:
    ColumnRecord()
      {
        add(m_tag);
      }
    Gtk::TreeModelColumn<Tag::Ptr> m_tag;
  };
  ColumnRecord                     m_columns;
  Glib::RefPtr<Gtk::ListStore>     m_tags;
  Glib::RefPtr<Gtk::TreeModelSort> m_sorted_tags;
  // The key for this dictionary is Tag.Name.ToLower ().
  typedef std::map<Glib::ustring, Gtk::TreeIter> TagMap;
  TagMap                           m_tag_map;
  typedef std::map<Glib::ustring, Tag::Ptr> InternalMap;
  InternalMap                      m_internal_tags;
  mutable Glib::Mutex              m_locker;
  
  sigc::signal<void, Tag::Ptr, const Gtk::TreeIter &> m_signal_tag_added;
  sigc::signal<void, const Glib::ustring &> m_signal_tag_removed;
};

}

#endif
