#
# MLDB-1718-invalid-utf-8-string-long.py
# Michael Burkat 2016-01-01
# This file is part of MLDB. Copyright 2016 Datacratic. All rights reserved.
#

import unittest

mldb = mldb_wrapper.wrap(mldb) # noqa

class Mldb1718(MldbUnitTest):
    def test_it(self):
        res = mldb.put("/v1/procedures/testset", {
            "type": "import.text",
            "params": {
                "dataFileUrl": "file://mldb/testing/dataset/MLDB-1718-long_string.txt",
                "delimiter": "\t",
                "headers": ['0'],
                "outputDataset": {
                    "id": "testset",
                    "type": "sparse.mutable",
                },
                "runOnCreation": True
            }
        })

        res = mldb.query("""select "0" from testset where rowName() = '1' """)
        mldb.log(res)
        self.assertEqual(res[1][1], "x")

        res = mldb.query("""select count(*) from (select "0" from testset) group by "0" """)
        mldb.log(res)

if __name__ == '__main__':
    mldb.run_tests()

