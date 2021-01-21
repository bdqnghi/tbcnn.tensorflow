from util.data.data_loader.rust_txl_data_loader import RustTxlDataLoader

def main():
    data_path = "OJ_rs/OJ_rs-buckets-train.pkl"
   
    processor = RustTxlDataLoader(data_path)

if __name__ == "__main__":
    main()
   