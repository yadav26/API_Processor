# API_Processor

## Building
git clone https://github.com/yadav26/API_Processor.git
cd ./API_Processor
### Windows cmake building
cmake -S . -B winbuild
cmake --build winbuild

### linux ubuntu cmake building
cmake -S . -B linuxbuild
cmake --build linuxbuild

## Design 

[Design Diagram](https://viewer.diagrams.net/?tags=%7B%7D&highlight=0000ff&edit=_blank&layers=1&nav=1#R5VtJc6M4GP01PraLHfmYbSY1NalKtQ8zmUuXDLJNGhAt5NieXz9SEItYbNkBk3hyMdrhfe%2FbJGVi3kW73wlM1k%2FYR%2BHE0PzdxLyfGIZuzwD74TX7rGbm2FnFigS%2B6FRWzIN%2FkajURO0m8FEqdaQYhzRI5EoPxzHyqFQHCcFbudsSh%2FKqCVyhRsXcg2Gz9q%2FAp2tRq2ta2fCIgtVaLA1s0bCA3s8VwZtYrDcxTIR89pc1RzCfS%2FRP19DH20qV%2BTAx7wjGNHuKdnco5NjmsGXjfutoLd6boJiqDNi%2B6H9Er%2BiX7sPN49vtP%2FPodf5NzPIGw43AY04JgtHtnjKhGE7Ipr5NExjzD6B7AZrza8Pf%2BraE4JuHQ0wm5g1fMA5oAEPWXvZkTyv%2B%2Bx1BH5F8Yvay2dxZo8CpWMZ4nxrx99dY83YdUDRPoMdbt4yNrG5NI7bQvV6MfkOEol0nRHoBPCM0whGiZM%2B65AOAkJXgsu6I8rbCjFye6wop8n5QkHFVTF0KhD0ImZwgH6Mhn9vNconIE4wZLzmQMOI4xIs0OYygfhkELTC1JQwNuwVDYDcxLIDtH0SrgWIDKOQzqyCKmNA1XuEYhg9l7a1MxrLPnxgnAsBXROlemDi4obgNXr7QYXDZe%2BEN8dCBLzKFoYRkhegh9XbbpUVQCGnwJr9I77ibDdjvA6bv1Ftz5o7N1JquW8bYuq7bx2nKrW3S%2BfXCR8JF3l07GRVXRsU0W1CxWlAxh0JFAZSUEvyz8N6GTBXmdhPeL9qteAAzXYZ4660hoVM%2FIAysHz6ksINxSjQ7IMtOmFu41ka1wUBVMIhfCNSxUHSuCkUxjTUyNcE1ggpGBjVPtq4LVX1sM%2BpeI6otOc9FQZ1dI6jFdsJYqBoKcdTXyoF0oX3HkyDQLprLJEF600jc4SiCsc8qH9lP%2BAmTIXv8ZKgZBzwT7KE0ZZUMQBhxAD8ZbI4qbO5gsDWt53eUJjhO0QG0xtldm7XYxAvvrimERSj2b%2Fg2Myt5IUzTwJOBkVFkUJD937wwtfPiS7XtfieV9nlpF9DKMFZ6EfPz53IQL%2BRj%2BrSlQNWWztpFXBGh3SLBvE7Z5IoVnnHAPqVgULEbkeubXWNG9qFiVEmOxkSWXZtIq02UAdGY6J1lxWd%2FgHjGZyFenyRS5JAxJoUsTZa81ReFrEtTqLm7%2Bv%2B0XYYi7cwxaWfYusSWRqCvSrvGRHXnODTt3CbLhk8bvox7HDXVyDl1YdnkZkOXjMbUdHVVw1GRaSnhdqm%2Bz%2FCMSMAgY4lT76K2VM3Jh0XdEeLYHZnYEUPRl36bzchEpKs3lJJgsaEofYJJUh7i%2B8FbeYCfVS1IvYa9i9Rv5MTNnskou23HXG6LO7CGSkXMce3qqRqYGWOrqvH6VDOOKfzAymvaisprdQQDH1Vex5CVV5ud5%2BXtWpTq1MOFgb28pXAK87V2C5WpYXakJ6dRg4XdcF%2FpkHBJpd3McSxZ4EDTDhLkSH%2F2kL1Bv76huYcsfMODH9DiStJHbPsyCMO77CoZG2v6EIElT1qyHf9Ki%2BMBtFgO4w1A2zZemzeo5479nc8PuTFlAjlQm4FzzHa763AP%2B45RbP2o%2Bw1OzZKDegSh6hJM4E7zu7a5V9ANJa9wqjEygbwOcC5gXPLAu0L5MuJsiTXnFBOkGF7mR4L85I%2BPe78SfNwU7VB%2BX7mnsLMR3LfdjdQuamicMfx6V8ro2scs0Rnxao82x1K%2Bd9lLcniq3lpWPWq0D5qURn%2FXvICeN%2FctRRBxLVpu1U8F9RYt1y%2Bq5SqH%2F6eFE%2BMqYleQPs4ZAjj3DMGuK6DiZu6phqG%2BjmtfwqEr3I7q54Di2D6jOvE%2BeTBpg5ksR6c2xbmHV0Dx8Opkj1TTlPyFhyXebJSYpjiicJiUKocUU00DqhtqDpC21LSpZrvnJmdD7rMZiupidtyK%2B%2Bh5CCuW%2FziX8ab870Tz4T8%3D)

## Classes descriptions

### CmdStreamReader
This is base class for stream tokenization and extract fully achieved commands.
#### CmdLineStreamReader
Child class derived from CmdStreamReader to read input from command line.
#### SocketStreamReader
Child class derived from CmdStreamReader to read input from listening server socket buffer.
#### FileStreamReader
Child class derived from CmdStreamReader to read input from file buffer .

### CmdBufferManager
This is filled with arrived full commands by StreamReader. It maintains a FIFO thread safe queue.

### CmdDispatcher
Dispatcher is the consumer of the buffer. It will wait till buffer available and send the buffers to process. Its life span goverened by CmdStreamReader.

### CmdValidator 
This is command handler to process the buffer. It validates the buffer command and generate appropriate response.


## AdminCommandEditor - Dynamic extension mode 
### CmdManager 
This class is responsible to mantain / update the command store and attribute mappings. Any command could be associated to listed attributes. This allows the editing of the commnads paired attributes.

### CmdAttributesMapper
This class is responsible for association of commands and attributes

### CmdStore
This class is storage of all commands and provides validity of commands names

### CmdAttributeStore
This class is storage of all attributes and provides validity of attribute names
