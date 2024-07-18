1. 修改路徑和檔名參數從這邊

      /FullLib/path_dir.h 
  
2. 修改分析參數和架設參數

      /FullLib/AnaVariable.h
   
4. 執行主程式可以再LINUX命令行輸入以下

       root -l /FullLib/MainControl_Convert_Selectio_PWidth.C
   
6. 如果需要生成假資料進行測試

     /FullLib/FakeDataGenerator.C

8. 更新完成，可以繪製不同板子上的PWIDTH分布，並且可包含簡易篩選的情況(紅色填滿)
   
     不同板子的結果是PwidthOfMTB(1,26).gif
   
     也可按照分層來繪製9449的所有頻道相對位置上的圖PwidthOfZ(0,4).gif
   
     圖片都放在Result資料夾裡面
   

主程式已大幅簡化，並可直接在ROOT6.30上運行
![image](https://github.com/user-attachments/assets/9af8de2c-e262-4b7d-bd76-79a90411f3bc)
剩下的內容分別是，建置成室內的路徑參數和複製程式碼，抓原始檔案，對原始檔案進行校正轉換為ROOT檔案

轉換後抓ROOT檔案，並進行基礎的資料時間區間分析，完成後進行事件切割(切割窗口28檔位=140TCNT~54.6ns)

最後進行PWidth的分析並作圖
