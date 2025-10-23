//
// Created by nekita on 02.09.25.
//

#include <gtest/gtest.h>
#include <netodo/db_manager/TaskDBManager.hpp>
#include <netodo/db_manager/ToDoDBManager.hpp>

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

TEST(DBTest, ToDoTableTest) {
    ToDoDBManager db("test.db");

    ToDo todo1("hello", "hi");
    int64_t id1 = db.AddToDo(todo1);

    ToDo found_todo = db.GetToDo(id1);
    ASSERT_EQ(found_todo.name, "hello");
    ASSERT_EQ(found_todo.short_name, "hi");
    ASSERT_EQ(found_todo.status, NoteStatus::NotStarted);

    ToDo todo2(101, 0, "Привет");
    int64_t id2 = db.AddToDo(todo2);
    std::vector<ToDo> ch = db.GetAllToDoByParent(101);
    ASSERT_EQ(ch.size(), 1);
    ASSERT_EQ(ch[0].id, id2);
    ASSERT_EQ(ch[0].name, "Привет");

    db.UpdateToDo(id2, ToDo("QWERTY", "abc", "", NoteStatus::InProgress));
    found_todo = db.GetToDo(id2);
    ASSERT_EQ(found_todo.name, "QWERTY");
    ASSERT_EQ(found_todo.short_name, "abc");
    ASSERT_EQ(found_todo.status, NoteStatus::InProgress);

    std::vector<ToDo> todos = db.GetAllToDo();
    ASSERT_EQ(todos.size(), 2);

    db.Clear();
}

TEST(DBTest, TaskTableTest) {
    TaskDBManager db("test.db");

    Task task1("hello", "hi");
    int64_t id1 = db.AddTask(task1);

    Task found_task = db.GetTask(id1);
    ASSERT_EQ(found_task.name, "hello");
    ASSERT_EQ(found_task.short_name, "hi");

    Task task2("ABC", "a", "abcdef");
    int64_t id2 = db.AddTask(task2);
    std::vector<Task> tasks = db.GetAllTask();
    ASSERT_EQ(tasks.size(), 2);
    ASSERT_EQ(tasks[0].name, "hello");
    ASSERT_EQ(tasks[1].name, "ABC");
    ASSERT_EQ(tasks[1].status, NoteStatus::NotStarted);

    task2.status = NoteStatus::InProgress;
    db.UpdateTask(id2, task2);

    found_task = db.GetTask(id2);
    ASSERT_EQ(found_task.name, "ABC");
    ASSERT_EQ(found_task.short_name, "a");
    ASSERT_EQ(found_task.status, NoteStatus::InProgress);

    db.Clear();
}

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}