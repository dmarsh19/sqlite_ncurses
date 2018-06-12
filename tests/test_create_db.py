#!/usr/bin/env python3
"""
"""
import os
import sys
import logging

import sqlite3 as sqlite

SQLITE_DB = "menu.sqlite"

TABLES = {
    "Menu": (
        ("Key", "INTEGER", "UNIQUE"),
        ("Description", "TEXT")
    ),
}

TABLE_SCHEMAS = {
    "Menu": ("Key", "Description")
}

TABLE_VALUES = {
    "Menu": (
        (0, "Apple"),
        (1, "Banana"),
        (2, "Orange")
    ),
}


class SQLiteManager(object):
    """Organizational class to group SQLite functions."""
    @staticmethod
    def create_table(conn, table_name, table_schema):
        """Create a table. Adds RowId field."""
        LOG.info('creating sqlite table [%s]', table_name)
        sql_str = ('CREATE TABLE IF NOT EXISTS "{0}" '
                   '(RowId INTEGER PRIMARY KEY,'
                   '{1})'.format(table_name, ','.join([' '.join(i) for i in table_schema])))
        with conn: # Context Manager to avoid manual rollbacks and commits
            conn.execute(sql_str)

    @staticmethod
    def add_column(conn, table_name, field_name, field_type):
        """Add a column to a table in a sqlite database."""
        LOG.info('Add column [%s] to [%s]', field_name, table_name)
        sql_str = 'ALTER TABLE {0} ADD COLUMN {1} {2}'.format(table_name, field_name, field_type)
        with conn:
            conn.execute(sql_str)

    @staticmethod
    def add_index(conn, table_name, field_name):
        """Add an index to a field in a sqlite database table."""
        LOG.info('CREATE INDEX [ix_%s_%s] on table [%s] field [%s]', table_name, field_name,
                 table_name, field_name)
        with conn:
            conn.execute('CREATE INDEX ix_{0}_{1} on {0}({1})'.format(table_name, field_name))

    @staticmethod
    def insert_rows(conn, table_name, table_schema, values):
        """."""
        sql = "INSERT INTO {0}({1}) VALUES({2})".format(table_name,','.join(table_schema),
                                                        ','.join(['?' for i in table_schema]))
        LOG.debug(sql)
        with conn:
            conn.executemany(sql, values)


def main():
    db_path = os.path.join(SQLITE_DB)

    LOG.info('connecting to db [%s]', db_path)
    conn = sqlite.connect(db_path)
    for table in TABLES:
        SQLiteManager.create_table(conn, table, TABLES[table])
    for table in TABLE_VALUES:
        SQLiteManager.insert_rows(conn, table, TABLE_SCHEMAS[table], TABLE_VALUES[table])
    conn.close()


if __name__ == '__main__':
    logging.basicConfig(stream=sys.stdout,
                        level=logging.DEBUG,#INFO,
                        format='%(asctime)s %(name)s %(levelname)s %(message)s')
    LOG = logging.getLogger(__name__)

    LOG.info('start')
    main()
    LOG.info('done')
