### Requirements:
- libsqlite3-dev
- libncurses5-dev

### Get Started:
1. Create a sqlite database in the project root directory (same location as this README)
```
./tests/test_create_db.py
```
2. Build project from source
```
make && make clean
```
3. Run executable, usage is documented if run with no params
```
./menu_from_sqlite menu.sqlite Menu "Key,Description"
```
>Press Enter to select an item and exit or Esc to exit without selecting.
