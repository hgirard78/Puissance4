set nocompatible
set encoding=utf-8 fileencodings=
colorscheme onedark
autocmd Filetype make setlocal noexpandtab
filetype off
set rtp+=~/.vim/bundle/Vundle.vim
call vundle#begin()
"""""""""""""""""""""""
"" Add new plugins here
"""""""""""""""""""""""
Plugin 'VundleVim/Vundle.vim'
Plugin 'vim-airline/vim-airline'
Plugin 'preservim/nerdtree'
Plugin 'joshdick/onedark.vim'
"""""""""""""""""""""""
"" End of plugin list
"""""""""""""""""""""""
call vundle#end()
syntax on
filetype plugin indent on
filetype plugin on
set number
set cc=80
set expandtab
set shiftwidth=4
set softtabstop=4
set smartindent
set autoindent
inoremap <expr> ) strpart(getline('.'), col('.')-1, 1) == ")" ? "\<Right>" : ")"
inoremap <expr> ; strpart(getline('.'), col('.')-1, 1) == ")" ? "\<End>;" : ";"
execute pathogen#infect()
autocmd StdinReadPre * let s:std_in=1
autocmd VimEnter * if argc() == 1 && isdirectory(argv()[0]) && !exists("s:std_in") | exe 'NERDTree' argv()[0] | wincmd p | ene | exe 'cd '.argv()[0] | endif
map <C-o> :NERDTreeToggle<CR>
inoremap { {}<ESC>ha
inoremap [ []<Esc>ha
inoremap ( ()<Esc>ha
inoremap " ""<Esc>ha
inoremap ' ''<Esc>ha

