import urllib.request
import zipfile
from tqdm import tqdm
import os
import argparse

class DownloadProgressBar(tqdm):
    def update_to(self, b=1, bsize=1, tsize=None):
        if tsize is not None:
            self.total = tsize
        self.update(b * bsize - self.n)


def download_url(url, output_path):
    with DownloadProgressBar(unit='B', unit_scale=True,
                             miniters=1, desc=url.split('/')[-1]) as t:
        urllib.request.urlretrieve(url, filename=output_path, reporthook=t.update_to)

def parse_arguments(): 
    parser = argparse.ArgumentParser()
    parser.add_argument('--url', default="https://ai4code.s3-ap-southeast-1.amazonaws.com/OJ104_pycparser_train_test_val.zip")
    parser.add_argument('--output_path',default="../OJ104_pycparser_train_test_val.zip")
    opt = parser.parse_args(),
    return opt


def main(opt):

    url = opt.url
    output_path = opt.output_path


    if not os.path.exists(output_path):
        download_url(url, output_path)


    with zipfile.ZipFile(output_path) as zf:
        for member in tqdm(zf.infolist(), desc='Extracting '):
            try:
                zf.extract(member, "../")
            except zipfile.error as e:
                pass


if __name__ == "__main__":
    opt = parse_arguments()
    main(opt[0])
   
