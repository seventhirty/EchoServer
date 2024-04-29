#pragma once

class EchoServerApp
{
public:
  int Run(int argc, char *argv[]) const;
private:
  int ResolvePort(int argc, char *argv[]) const;
};