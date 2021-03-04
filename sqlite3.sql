CREATE TABLE teachers(
	id INTEGER PRIMARY KEY AUTOINCREMENT,
	code CHAR(10) NOT NULL UNIQUE,
	name CHAR(25) NOT NULL
);

CREATE TABLE courses(
	id INTEGER PRIMARY KEY AUTOINCREMENT,
	code CHAR(5) NOT NULL UNIQUE,
	name CHAR(25) NOT NULL,
	teacher_id INTEGER,
	course_id INTEGER,
	FOREIGN KEY(teacher_id) REFERENCES teachers(id),
	FOREIGN KEY(course_id) REFERENCES courses(id)
);

CREATE TABLE students(
	id INTEGER PRIMARY KEY AUTOINCREMENT,
	code CHAR(10) NOT NULL UNIQUE,
	name CHAR(25)
);

CREATE TABLE grades(
	id INTEGER PRIMARY KEY AUTOINCREMENT,
	grade1 INTEGER,
	grade2 INTEGER,
	grade3 INTEGER,
	average INTEGER,
	student_id INTEGER NOT NULL,
	course_id INTEGER NOT NULL, 
	FOREIGN KEY(student_id) REFERENCES students(id),
	FOREIGN KEY(course_id) REFERENCES courses(id)
);