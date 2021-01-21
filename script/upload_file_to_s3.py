import boto3
from botocore.exceptions import ClientError

BUCKET_NAME = "treecaps"

ACCESS_KEY = 'AKIA3VN476GJNA2XN3MN'
SECRET_KEY = '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'


def upload_file(file_name, bucket, object_name=None):
    if object_name is None:
        object_name = file_name
    s3_client = boto3.client('s3', aws_access_key_id=ACCESS_KEY,aws_secret_access_key=SECRET_KEY)
    try:
        response = s3_client.upload_file(file_name, bucket, object_name)
    except ClientError as e:
        logging.error(e)
        return False
    return True

upload_file("../OJ_srcml_train_test_val.zip", BUCKET_NAME, "OJ_srcml_train_test_val.zip")