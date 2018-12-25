try
{
  // Creating an object of CSVReader
  CSVReader reader("../data/Student.csv");

  // Get the data from CSV File
  std::vector<std::vector<std::string> > dataList = reader.getData();

  // Print the content of row by row on screen
  for(std::vector<std::string> vec : dataList)
  {
    for(std::string data : vec)
    {
      std::cout<<data<<"\t";
    }
    std::cout<<std::endl;
  }

  CSVWriter writer("StudentW.csv");
  for (std::vector<std::string> v : dataList)
  {
    writer.addDatainRow(v.begin(), v.end());
  }
}
catch(const angru::system::exception::error& e)
{
  std::cerr<<"Error: "<<e.what()<<std::endl;
  return 1;
}
catch(...)
{
  std::cerr<<"Error: unknown exception"<<std::endl;
  return 2;
}
