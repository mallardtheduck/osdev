find ./data/ -type f | xargs -I{} xxd -i {} > xxd_data.inc
