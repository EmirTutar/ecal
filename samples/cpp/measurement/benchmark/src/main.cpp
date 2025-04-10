/* ========================= eCAL LICENSE =================================
 *
 * Copyright (C) 2016 - 2024 Continental Corporation
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 * 
 *      http://www.apache.org/licenses/LICENSE-2.0
 * 
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * ========================= eCAL LICENSE =================================
*/

#include <chrono>
#include <fstream>
#include <iostream>
#include <string>
#include <thread>

#include <ecalhdf5/eh5_meas.h>

#define TEST_RAW_PERF      1
#define TEST_HDF5_PERF     1

#define USE_OFSTREAM       0
#define TEST_POST_SLEEP    2               // seconds

#define DATA_SET_SIZE_1    (1024)          // 1 kB
#define DATA_SET_NUMBER_1  (64*1024)

#define DATA_SET_SIZE_2    (128*1024)      // 128 kB
#define DATA_SET_NUMBER_2  (8*1024)

#define DATA_SET_SIZE_3    (1024*1024)     // 1 MB
#define DATA_SET_NUMBER_3  (1024)

#define DATA_SET_SIZE_4    (4096*1024)     // 4 MB
#define DATA_SET_NUMBER_4  (256)

namespace
{
  // properties
  std::string output_dir = "measurement_dir";
  const size_t max_size_per_file = 500;  // MB
  std::vector<char> data;
}

void MeasPerf(const std::string& file_name, const size_t pkg_size, const size_t pkg_num)
{
  data.resize(pkg_size);
  const size_t write_loops(pkg_num);

#if TEST_RAW_PERF
  // Test raw performance
  {
    // start time
    auto start = std::chrono::high_resolution_clock::now();

#if USE_OFSTREAM

    std::ofstream rfile(file_name + "_raw", std::ios::trunc | std::ios::out | std::ios::binary);
    if (rfile)
    {
      for (size_t loops = 0; loops < write_loops; ++loops)
      {
        rfile.write(data.data(), data.size());
      }
    }
    rfile.close();

#else // USE_OFSTREAM

    FILE* pFile(nullptr);
    std::string fname = file_name + "_raw";
    pFile = fopen(fname.c_str(), "wb");
    if (pFile)
    {
      for (size_t loops = 0; loops < write_loops; ++loops)
      {
        fwrite(data.data(), 1, data.size(), pFile);
      }
      fclose(pFile);
    }

#endif // USE_OFSTREAM

    // end time
    auto finish = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = finish - start;
    size_t sum_data = data.size() * write_loops;
    std::cout << std::endl;
    std::cout << "Packages number : " << write_loops << std::endl;
    std::cout << "Packages size   : " << data.size()/1024 << " kB" << std::endl;
    std::cout << "Sum payload     : " << sum_data / (1024*1024) << " MB" << std::endl;
    std::cout << "Throughput RAW  : " << int((sum_data / (1024.0 * 1024.0)) / elapsed.count()) << " MB/s " << std::endl;
    std::cout << std::endl;

    std::this_thread::sleep_for(std::chrono::seconds(TEST_POST_SLEEP));
  }
#endif

#if TEST_HDF5_PERF
  // Test HDF5 performance
  {
    // start time
    auto start = std::chrono::high_resolution_clock::now();

    eCAL::eh5::v2::HDF5Meas writer(output_dir, eCAL::eh5::v2::CREATE);
    writer.SetFileBaseName(file_name + "_hdf5");
    writer.SetMaxSizePerFile(max_size_per_file);
    for (size_t loop = 0; loop < write_loops; ++loop)
    {
      writer.AddEntryToFile(static_cast<void*>(data.data()), data.size(), 0, 0, "myChannel", 0, loop);
    }
    writer.Close();

    // end time
    auto finish = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = finish - start;
    size_t sum_data = data.size() * write_loops;
    std::cout << std::endl;
    std::cout << "Packages number : " << write_loops << std::endl;
    std::cout << "Packages size   : " << data.size() / 1024 << " kB" << std::endl;
    std::cout << "Sum payload     : " << sum_data / (1024 * 1024) << " MB" << std::endl;
    std::cout << "Throughput HDF5 : " << int((sum_data / (1024.0 * 1024.0)) / elapsed.count()) << " MB/s " << std::endl;
    std::cout << std::endl;

    std::this_thread::sleep_for(std::chrono::seconds(TEST_POST_SLEEP));
  }
#endif
}

int main()
{
  MeasPerf("meas_1_pkg",    DATA_SET_SIZE_1, DATA_SET_NUMBER_1);
  
  MeasPerf("meas_128_pkg",  DATA_SET_SIZE_2, DATA_SET_NUMBER_2);
  
  MeasPerf("meas_1024_pkg", DATA_SET_SIZE_3, DATA_SET_NUMBER_3);
  
  MeasPerf("meas_4096_pkg", DATA_SET_SIZE_4, DATA_SET_NUMBER_4);
}
