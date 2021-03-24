#!/usr/bin/env python3

"""
This example shows how to parse a csv file by reading it
line by line and split the data into list elements
"""

import sys
import tempfile
import os
import requests
from datetime import date

rki_url = "https://www.rki.de/DE/Content/InfAZ/N/Neuartiges_Coronavirus/Projekte_RKI/Nowcasting_Zahlen_csv.csv?__blob=publicationFile"

def clean_tmp_file(filename):
    try:
        stats = os.stat(filename)
        os.remove(filename)
    except FileNotFoundError:
        # nothing to clean up
        return

def download_rki_file(filename):
    clean_tmp_file(filename)

    with requests.get(rki_url, allow_redirects=False) as data:
        with open(filename, 'wb') as f:
            f.write(data.content)

def read_lines(filename):
    lines = []
    with open(filename, 'r') as f:
        while line := f.readline():
            lines.append(line)

    return lines

def parse_csv_lines(lines):
    """
    Parse all CSV lines and returns a list of dictionaries. Each dict contains the
    data set for the hole day
    """

    days = []

    # first_line containes the header
    # last 18 lines contains some explanation we don't want
    for line in lines[1:len(lines)-18]:
        day = parse_day_line(line) 
        days.append(day)

    return days

def parse_day_line(line):
    """
    Parse the day data set from the line
    """

    day = {}


def main():
    """
    Main function
    """

    # argv = sys.argv[1:] # this removes the binary name
    # if len(argv) == 0:
        # sys.stderr.write("Not enough arguments\n")
        # sys.stderr.write(f'Try {sys.argv[0]} <FILENAME>')
        # sys.stderr.write("\n")
        # sys.exit(1)

    # lines = readcsv(argv[0])

    # print(lines)

    filename = f'/tmp/.csv-{date.today().isoformat()}.csv'

    download_rki_file(filename)
    lines = read_lines(filename)
    parse_csv_lines(lines)

if __name__ == '__main__':
    main()
