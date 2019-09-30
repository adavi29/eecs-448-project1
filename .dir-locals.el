;;; -*- lexical-binding: t; -*-
;;; .dir-locals.el ---

;; Copyright (C) 2019  Zach Pearson

;; Author: Zach Pearson <zach@zjp.codes>
;; Keywords:

;; This file is not part of GNU Emacs.

;; This file is free software; you can redistribute it and/or modify
;; it under the terms of the GNU General Public License as published by
;; the Free Software Foundation, either version 3 of the License, or
;; (at your option) any later version.

;; This file is distributed in the hope that it will be useful,
;; but WITHOUT ANY WARRANTY; without even the implied warranty of
;; MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
;; GNU General Public License for more details.

;; You should have received a copy of the GNU General Public License
;; along with this file.  If not, see <https://www.gnu.org/licenses/>.

;;; Commentary:

;; Forces Emacs to adhere to the project's coding style, regardless of personal
;; init preferences.

;;; Code:

((c++-mode . ((indent-tabs-mode . t)
              ;; Standardize tab widths to GitHub
              (tab-width . 8)
              (c-basic-offset . 8)
              ;; Spaces for alignment; tabs for indentation
              (eval . (if (package-installed-p 'smart-tabs-mode)
                          (smart-tabs-mode 1))))))


(provide '.dir-locals)
;;; .dir-locals.el ends here
