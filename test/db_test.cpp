//
// Created by nekita on 02.09.25.
//

#include <gtest/gtest.h>

#include "netodo/db_manager/DBManager.hpp"

TEST(DBTest, NoteTableTest) {
    DBManager db("test.db");

    Note note("hello");
    int64_t id = db.AddNote(note);

    Note found_note = db.GetNote(id);
    ASSERT_EQ(found_note.name, note.name);

    Note note1("hi");
    int64_t id1 = db.AddNote(note1);
    found_note = db.GetNote(id);
    ASSERT_EQ(found_note.name, note.name);

    std::vector<Note> notes = db.GetAllNotes();
    ASSERT_EQ(notes.size(), 2);
    ASSERT_EQ(notes[0].name, note.name);
    ASSERT_EQ(notes[1].name, note1.name);

    db.Clear();
}