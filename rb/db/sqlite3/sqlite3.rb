#!/usr/bin/env ruby

require 'sqlite3'

class MySqliteHelper
  DBNAME = 'test.sqlite'
  
  def initialize(argv)
    File.delete(DBNAME) if File.exists?(DBNAME)
    @db = SQLite3::Database.new(DBNAME)
    @db.execute("CREATE TABLE testdata(id integer primary key autoincrement, name varchar(100))")
    argv.each do |param|
      @db.execute("INSERT INTO testdata(name) VALUES(\"#{param}\")")
    end
  end
  
  def insert_name(name)
    @db.execute("INSERT INTO testdata(name) VALUES(\"#{name}\")")
  end

  def show
    response = @db.execute("SELECT * FROM testdata")
    response.each do |row|
      puts row
    end
  end
end

sql = MySqliteHelper.new(ARGV)

sql.insert_name("Mama")
sql.insert_name("Papa")

sql.show
